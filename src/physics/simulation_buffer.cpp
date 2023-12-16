#include "physics/simulation_buffer.hpp"

#include "common/airplane_info.hpp"
#include "physics/player_info.hpp"
#include "physics/player_input.hpp"
#include "physics/player_state.hpp"
#include "physics/simulation_buffer_element.hpp"
#include "physics/simulation_buffer_player.hpp"
#include "physics/timestep.hpp"

#include <array>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Physics
{
	SimulationBuffer::SimulationBuffer(int ownId) :
		m_ownId{ownId}
	{ }

	void SimulationBuffer::writeControlFrame(const Timestep& timestep, int playerId,
		const PlayerInput& playerInput)
	{
		m_buffer[timestep.frame].mutex.lock();

		bool isSecondOdd = timestep.second % 2;
		if (!m_buffer[timestep.frame].players.contains(playerId))
		{
			m_buffer[timestep.frame].players.insert({playerId,
				SimulationBufferPlayer
				{
					std::array<bool, 2>
					{
						!isSecondOdd,
						isSecondOdd
					},
					PlayerInfo
					{
						playerInput,
						PlayerState{}
					}
				}});
		}
		else if ((!isSecondOdd &&
			!m_buffer[timestep.frame].players.at(playerId).hasControlFrame[0]) ||
			(isSecondOdd && !m_buffer[timestep.frame].players.at(playerId).hasControlFrame[1]))
		{
			m_buffer[timestep.frame].players.at(playerId).hasControlFrame[isSecondOdd] = true;
			m_buffer[timestep.frame].players.at(playerId).info.input = playerInput;
		}

		m_buffer[timestep.frame].mutex.unlock();
	}

	void SimulationBuffer::writeStateFrame(const Timestep& timestep,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		m_buffer[timestep.frame].mutex.lock();

		removePlayerInputs(timestep, playerInfos);
		addAndUpdatePlayerInputs(timestep, playerInfos);
		m_buffer[timestep.frame].hasStateFrame = true;

		m_buffer[timestep.frame].mutex.unlock();
	}

	bool SimulationBuffer::setOwnInput(const Timestep& timestep,
		const PlayerInput& ownInput)
	{
		m_buffer[timestep.frame].mutex.lock();

		bool isSecondOdd = timestep.second % 2;
		bool inputSet = false;
		if (!m_buffer[timestep.frame].players.contains(m_ownId))
		{
			m_buffer[timestep.frame].players.insert({m_ownId,
				SimulationBufferPlayer
				{
					std::array<bool, 2>
					{
						!isSecondOdd,
						isSecondOdd
					},
					PlayerInfo
					{
						ownInput,
						PlayerState{}
					}
				}});
			inputSet = true;
		}
		else if ((!isSecondOdd &&
			!m_buffer[timestep.frame].players.at(m_ownId).hasControlFrame[0]) ||
			(isSecondOdd && !m_buffer[timestep.frame].players.at(m_ownId).hasControlFrame[1]))
		{
			m_buffer[timestep.frame].players.at(m_ownId).hasControlFrame[isSecondOdd] = true;
			m_buffer[timestep.frame].players.at(m_ownId).info.input = ownInput;
			inputSet = true;
		}

		m_buffer[timestep.frame].mutex.unlock();

		return inputSet;
	}

	void SimulationBuffer::update(const Timestep& timestep)
	{
		Timestep previousTimestep = timestep.previous();

		m_buffer[previousTimestep.frame].mutex.lock();
		m_buffer[timestep.frame].mutex.lock();
		
		if (!m_buffer[timestep.frame].hasStateFrame)
		{
			removePlayerInputs(previousTimestep, timestep);
			addAndUpdatePlayerInputs(previousTimestep, timestep);
		}
		std::unordered_map<int, PlayerInfo> playerInfos;
		for (const std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[timestep.frame].players)
		{
			playerInfos.insert({player.first, player.second.info});
		}
		bool hasStateFrame = m_buffer[timestep.frame].hasStateFrame;
		m_buffer[timestep.frame].hasStateFrame = false;
		
		m_buffer[previousTimestep.frame].mutex.unlock();
		m_buffer[timestep.frame].mutex.unlock();

		updateScene(previousTimestep, timestep, playerInfos, hasStateFrame);
	}

	std::unordered_map<int, Common::AirplaneInfo> SimulationBuffer::getAirplaneInfos(
		const Timestep& timestep)
	{
		m_buffer[timestep.frame].mutex.lock();

		std::unordered_map<int, Common::AirplaneInfo> airplaneInfos =
			m_buffer[timestep.frame].scene.getAirplaneInfos();

		m_buffer[timestep.frame].mutex.unlock();

		return airplaneInfos;
	}

	void SimulationBuffer::removePlayerInputs(const Timestep& timestep,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[timestep.frame].players)
		{
			if (!playerInfos.contains(player.first))
			{
				keysToBeDeleted.push_back(player.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[timestep.frame].players.erase(key);
		}
	}

	void SimulationBuffer::addAndUpdatePlayerInputs(const Timestep& timestep,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		bool isSecondOdd = timestep.second % 2;
		for (const std::pair<const int, PlayerInfo>& playerInfo : playerInfos)
		{
			m_buffer[timestep.frame].players[playerInfo.first].hasControlFrame[isSecondOdd] = true;
			m_buffer[timestep.frame].players[playerInfo.first].info = playerInfo.second;
		}
	}

	void SimulationBuffer::removePlayerInputs(const Timestep& previousTimestep,
		const Timestep& timestep)
	{
		std::vector<int> keysToBeDeleted;
		for (std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[timestep.frame].players)
		{
			if (!m_buffer[previousTimestep.frame].players.contains(player.first))
			{
				keysToBeDeleted.push_back(player.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[timestep.frame].players.erase(key);
		}
	}

	void SimulationBuffer::addAndUpdatePlayerInputs(const Timestep& previousTimestep,
		const Timestep& timestep)
	{
		bool isSecondOdd = timestep.second % 2;
		for (const std::pair<const int, SimulationBufferPlayer>& previousTimestepPlayer :
			m_buffer[previousTimestep.frame].players)
		{
			if (!m_buffer[timestep.frame].players.contains(previousTimestepPlayer.first))
			{
				m_buffer[timestep.frame].players.insert({previousTimestepPlayer.first,
					SimulationBufferPlayer
					{
						std::array<bool, 2>
						{
							false,
							false
						},
						PlayerInfo
						{
							previousTimestepPlayer.second.info.input,
							PlayerState{}
						}
					}});
			}
			else if (!m_buffer[timestep.frame].players[previousTimestepPlayer.first].
				hasControlFrame[isSecondOdd])
			{
				m_buffer[timestep.frame].players[previousTimestepPlayer.first].info.input =
					previousTimestepPlayer.second.info.input;
			}
		}
		for (std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[timestep.frame].players)
		{
			player.second.hasControlFrame[!isSecondOdd] = false;
		}
	}

	void SimulationBuffer::updateScene(const Timestep& previousTimestep,
		const Timestep& timestep, const std::unordered_map<int, PlayerInfo>& playerInfos,
		bool hasStateFrame)
	{
		if (hasStateFrame)
		{
			m_buffer[timestep.frame].scene.updateWithStateFrame(
				m_buffer[previousTimestep.frame].scene, playerInfos);
		}
		else
		{
			m_buffer[timestep.frame].scene.updateWithoutStateFrame(
				m_buffer[previousTimestep.frame].scene, playerInfos);
		}
	}
};
