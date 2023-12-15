#include "physics/simulation_buffer.hpp"

#include "common/airplane_info.hpp"
#include "physics/simulation_buffer_element.hpp"
#include "physics/simulation_buffer_user.hpp"
#include "physics/timestep.hpp"
#include "physics/user_info.hpp"
#include "physics/user_input.hpp"
#include "physics/user_state.hpp"

#include <array>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Physics
{
	SimulationBuffer::SimulationBuffer(int ownId) :
		m_ownId{ownId}
	{ }

	void SimulationBuffer::writeControlFrame(const Timestep& timestep, int userId,
		const UserInput& userInput)
	{
		m_buffer[timestep.frame].mutex.lock();

		bool isSecondOdd = timestep.second % 2;
		if (!m_buffer[timestep.frame].users.contains(userId))
		{
			m_buffer[timestep.frame].users.insert({userId,
				SimulationBufferUser
				{
					std::array<bool, 2>
					{
						!isSecondOdd,
						isSecondOdd
					},
					UserInfo
					{
						userInput,
						UserState{}
					}
				}});
		}
		else if ((!isSecondOdd && !m_buffer[timestep.frame].users.at(userId).hasControlFrame[0]) ||
			(isSecondOdd && !m_buffer[timestep.frame].users.at(userId).hasControlFrame[1]))
		{
			m_buffer[timestep.frame].users.at(userId).hasControlFrame[isSecondOdd] = true;
			m_buffer[timestep.frame].users.at(userId).info.input = userInput;
		}

		m_buffer[timestep.frame].mutex.unlock();
	}

	void SimulationBuffer::writeStateFrame(const Timestep& timestep,
		const std::unordered_map<int, UserInfo>& userInfos)
	{
		m_buffer[timestep.frame].mutex.lock();

		removeUserInputs(timestep, userInfos);
		addAndUpdateUserInputs(timestep, userInfos);
		m_buffer[timestep.frame].hasStateFrame = true;

		m_buffer[timestep.frame].mutex.unlock();
	}

	bool SimulationBuffer::setOwnInput(const Timestep& timestep,
		const UserInput& ownInput)
	{
		m_buffer[timestep.frame].mutex.lock();

		bool isSecondOdd = timestep.second % 2;
		bool inputSet = false;
		if (!m_buffer[timestep.frame].users.contains(m_ownId))
		{
			m_buffer[timestep.frame].users.insert({m_ownId,
				SimulationBufferUser
				{
					std::array<bool, 2>
					{
						!isSecondOdd,
						isSecondOdd
					},
					UserInfo
					{
						ownInput,
						UserState{}
					}
				}});
			inputSet = true;
		}
		else if ((!isSecondOdd && !m_buffer[timestep.frame].users.at(m_ownId).hasControlFrame[0]) ||
			(isSecondOdd && !m_buffer[timestep.frame].users.at(m_ownId).hasControlFrame[1]))
		{
			m_buffer[timestep.frame].users.at(m_ownId).hasControlFrame[isSecondOdd] = true;
			m_buffer[timestep.frame].users.at(m_ownId).info.input = ownInput;
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
			removeUserInputs(previousTimestep, timestep);
			addAndUpdateUserInputs(previousTimestep, timestep);
		}
		std::unordered_map<int, UserInfo> userInfos;
		for (const std::pair<const int, SimulationBufferUser>& user :
			m_buffer[timestep.frame].users)
		{
			userInfos.insert({user.first, user.second.info});
		}
		bool hasStateFrame = m_buffer[timestep.frame].hasStateFrame;
		m_buffer[timestep.frame].hasStateFrame = false;
		
		m_buffer[previousTimestep.frame].mutex.unlock();
		m_buffer[timestep.frame].mutex.unlock();

		updateScene(previousTimestep, timestep, userInfos, hasStateFrame);
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

	void SimulationBuffer::removeUserInputs(const Timestep& timestep,
		const std::unordered_map<int, UserInfo>& userInfos)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, SimulationBufferUser>& user :
			m_buffer[timestep.frame].users)
		{
			if (!userInfos.contains(user.first))
			{
				keysToBeDeleted.push_back(user.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[timestep.frame].users.erase(key);
		}
	}

	void SimulationBuffer::addAndUpdateUserInputs(const Timestep& timestep,
		const std::unordered_map<int, UserInfo>& userInfos)
	{
		bool isSecondOdd = timestep.second % 2;
		for (const std::pair<const int, UserInfo>& userInfo : userInfos)
		{
			m_buffer[timestep.frame].users[userInfo.first].hasControlFrame[isSecondOdd] = true;
			m_buffer[timestep.frame].users[userInfo.first].info = userInfo.second;
		}
	}

	void SimulationBuffer::removeUserInputs(const Timestep& previousTimestep,
		const Timestep& timestep)
	{
		std::vector<int> keysToBeDeleted;
		for (std::pair<const int, SimulationBufferUser>& user : m_buffer[timestep.frame].users)
		{
			if (!m_buffer[previousTimestep.frame].users.contains(user.first))
			{
				keysToBeDeleted.push_back(user.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[timestep.frame].users.erase(key);
		}
	}

	void SimulationBuffer::addAndUpdateUserInputs(const Timestep& previousTimestep,
		const Timestep& timestep)
	{
		bool isSecondOdd = timestep.second % 2;
		for (const std::pair<const int, SimulationBufferUser>& previousUser :
			m_buffer[previousTimestep.frame].users)
		{
			if (!m_buffer[timestep.frame].users.contains(previousUser.first))
			{
				m_buffer[timestep.frame].users.insert({previousUser.first,
					SimulationBufferUser
					{
						std::array<bool, 2>
						{
							false,
							false
						},
						UserInfo
						{
							previousUser.second.info.input,
							UserState{}
						}
					}});
			}
			else if (!m_buffer[timestep.frame].users[previousUser.first].
				hasControlFrame[isSecondOdd])
			{
				m_buffer[timestep.frame].users[previousUser.first].info.input =
					previousUser.second.info.input;
			}
		}
		for (std::pair<const int, SimulationBufferUser>& user : m_buffer[timestep.frame].users)
		{
			user.second.hasControlFrame[!isSecondOdd] = false;
		}
	}

	void SimulationBuffer::updateScene(const Timestep& previousTimestep,
		const Timestep& timestep, const std::unordered_map<int, UserInfo>& userInfos,
		bool hasStateFrame)
	{
		if (hasStateFrame)
		{
			m_buffer[timestep.frame].scene.updateWithStateFrame(
				m_buffer[previousTimestep.frame].scene, userInfos);
		}
		else
		{
			m_buffer[timestep.frame].scene.updateWithoutStateFrame(
				m_buffer[previousTimestep.frame].scene, userInfos);
		}
	}
};
