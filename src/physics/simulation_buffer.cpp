#include "physics/simulation_buffer.hpp"

#include "common/airplane_info.hpp"
#include "common/user_info.hpp"
#include "common/user_input.hpp"
#include "physics/simulation_buffer_element.hpp"
#include "physics/simulation_buffer_user.hpp"
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

	void SimulationBuffer::writeControlFrame(const Timestep& timestep, int userId,
		const Common::UserInput& userInput)
	{
		m_buffer[timestep.frame].mutex.lock();

		if (!m_buffer[timestep.frame].users.contains(userId))
		{
			m_buffer[timestep.frame].users.insert({userId,
				SimulationBufferUser
				{
					timestep.second,
					Common::UserInfo
					{
						userInput,
						Common::UserState{}
					}
				}});
		}
		else if (m_buffer[timestep.frame].users.at(userId).second != timestep.second)
		{
			m_buffer[timestep.frame].users.at(userId).second = timestep.second;
			m_buffer[timestep.frame].users.at(userId).info.input = userInput;
		}

		m_buffer[timestep.frame].mutex.unlock();
	}

	void SimulationBuffer::writeStateFrame(const Timestep& timestep,
		const std::unordered_map<int, Common::UserInfo>& userInfos)
	{
		m_buffer[timestep.frame].mutex.lock();

		removeUserInputs(timestep, userInfos);
		addAndUpdateUserInputs(timestep, userInfos);
		m_buffer[timestep.frame].hasStateFrame = true;

		m_buffer[timestep.frame].mutex.unlock();
	}

	bool SimulationBuffer::setOwnInput(const Timestep& timestep,
		const Common::UserInput& ownInput)
	{
		m_buffer[timestep.frame].mutex.lock();

		bool inputSet = false;
		if (!m_buffer[timestep.frame].users.contains(m_ownId))
		{
			m_buffer[timestep.frame].users.insert({m_ownId,
				SimulationBufferUser
				{
					timestep.second,
					Common::UserInfo
					{
						ownInput,
						Common::UserState{}
					}
				}});
			inputSet = true;
		}
		else if (m_buffer[timestep.frame].users.at(m_ownId).second != timestep.second)
		{
			m_buffer[timestep.frame].users.at(m_ownId).second = timestep.second;
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
		std::unordered_map<int, Common::UserInfo> userInfos;
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
		const std::unordered_map<int, Common::UserInfo>& userInfos)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, SimulationBufferUser>& bufferUserInfo :
			m_buffer[timestep.frame].users)
		{
			if (!userInfos.contains(bufferUserInfo.first))
			{
				keysToBeDeleted.push_back(bufferUserInfo.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[timestep.frame].users.erase(key);
		}
	}

	void SimulationBuffer::addAndUpdateUserInputs(const Timestep& timestep,
		const std::unordered_map<int, Common::UserInfo>& userInfos)
	{
		for (const std::pair<const int, Common::UserInfo>& userInfo : userInfos)
		{
			m_buffer[timestep.frame].users[userInfo.first].second = timestep.second;
			m_buffer[timestep.frame].users[userInfo.first].info = userInfo.second;
		}
	}

	void SimulationBuffer::removeUserInputs(const Timestep& previousTimestep,
		const Timestep& timestep)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, SimulationBufferUser>& userInfo :
			m_buffer[timestep.frame].users)
		{
			if (!m_buffer[previousTimestep.frame].users.contains(userInfo.first))
			{
				keysToBeDeleted.push_back(userInfo.first);
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
		for (const std::pair<const int, SimulationBufferUser>& previousUserInfo :
			m_buffer[previousTimestep.frame].users)
		{
			if (!m_buffer[timestep.frame].users.contains(previousUserInfo.first))
			{
				m_buffer[timestep.frame].users.insert({previousUserInfo.first,
					SimulationBufferUser
					{
						secondsPerMinute, // invalid value
						Common::UserInfo
						{
							previousUserInfo.second.info.input,
							Common::UserState{}
						}
					}});
			}
			else if (m_buffer[timestep.frame].users[previousUserInfo.first].second !=
				timestep.second)
			{
				m_buffer[timestep.frame].users[previousUserInfo.first].info.input =
					previousUserInfo.second.info.input;
			}
		}
	}

	void SimulationBuffer::updateScene(const Timestep& previousTimestep,
		const Timestep& timestep, const std::unordered_map<int, Common::UserInfo>& userInfos,
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
