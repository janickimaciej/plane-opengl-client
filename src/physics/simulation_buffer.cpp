#include "physics/simulation_buffer.hpp"

#include "common/sync/user_info.hpp"
#include "common/sync/user_input.hpp"
#include "physics/simulation_buffer_element.hpp"

#include <array>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Physics
{
	SimulationBuffer::SimulationBuffer(int ownId) :
		m_ownId{ownId}
	{ }

	void SimulationBuffer::writeControlFrame(int second, unsigned int frame, int id,
		const Common::UserInput& input)
	{
		m_buffer[frame].mutex.lock();

		if (!m_buffer[frame].userInfos.contains(id))
		{
			m_buffer[frame].userInfos.insert({id, Common::UserInfo
				{
					second,
					input,
					Common::UserState{}
				}});
		}
		else if (m_buffer[frame].userInfos.at(id).second != second)
		{
			m_buffer[frame].userInfos.at(id).input = input;
			m_buffer[frame].userInfos.at(id).second = second;
		}

		m_buffer[frame].mutex.unlock();
	}

	void SimulationBuffer::writeStateFrame(unsigned int frame,
		const std::unordered_map<int, Common::UserInfo>& userInfos)
	{
		m_buffer[frame].mutex.lock();

		removeUserInputs(frame, userInfos);
		addAndUpdateUserInputs(frame, userInfos);
		m_buffer[frame].hasStateFrame = true;

		m_buffer[frame].mutex.unlock();
	}

	void SimulationBuffer::setOwnInput(int second, unsigned int frame,
		const Common::UserInput& ownInput)
	{
		m_buffer[frame].mutex.lock();

		if (!m_buffer[frame].userInfos.contains(m_ownId))
		{
			m_buffer[frame].userInfos.insert({m_ownId,
				Common::UserInfo{second, ownInput, Common::UserState{}}});
		}
		else if (m_buffer[frame].userInfos.at(m_ownId).second != second)
		{
			m_buffer[frame].userInfos.at(m_ownId).input = ownInput;
			m_buffer[frame].userInfos.at(m_ownId).second = second;
		}

		m_buffer[frame].mutex.unlock();
	}

	void SimulationBuffer::update(int second, unsigned int frame)
	{
		unsigned int previousFrame = frame == 0 ? simulationBufferSize - 1 : frame - 1;

		m_buffer[previousFrame].mutex.lock();
		m_buffer[frame].mutex.lock();
		
		if (!m_buffer[frame].hasStateFrame)
		{
			removeUserInputs(previousFrame, frame);
			addAndUpdateUserInputs(second, previousFrame, frame);
		}
		std::unordered_map<int, Common::UserInfo> userInfos = m_buffer[frame].userInfos;
		bool hasStateFrame = m_buffer[frame].hasStateFrame;
		m_buffer[frame].hasStateFrame = false;
		
		m_buffer[previousFrame].mutex.unlock();
		m_buffer[frame].mutex.unlock();

		updateScene(previousFrame, frame, userInfos, hasStateFrame);
	}

	std::unordered_map<int, Common::AirplaneInfo> SimulationBuffer::getAirplaneInfos(
		unsigned int frame)
	{
		m_buffer[frame].mutex.lock();

		std::unordered_map<int, Common::AirplaneInfo> airplaneInfos =
			m_buffer[frame].scene.getAirplaneInfos();

		m_buffer[frame].mutex.unlock();

		return airplaneInfos;
	}

	void SimulationBuffer::removeUserInputs(unsigned int frame,
		const std::unordered_map<int, Common::UserInfo>& userInfos)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, Common::UserInfo>& bufferUserInfo :
			m_buffer[frame].userInfos)
		{
			if (!userInfos.contains(bufferUserInfo.first))
			{
				keysToBeDeleted.push_back(bufferUserInfo.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[frame].userInfos.erase(key);
		}
	}

	void SimulationBuffer::addAndUpdateUserInputs(unsigned int frame,
		const std::unordered_map<int, Common::UserInfo>& userInfos)
	{
		for (const std::pair<const int, Common::UserInfo>& frameUserInfo : userInfos)
		{
			m_buffer[frame].userInfos[frameUserInfo.first] = frameUserInfo.second;
		}
	}

	void SimulationBuffer::removeUserInputs(unsigned int previousFrame, unsigned int frame)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, Common::UserInfo>& userInfo : m_buffer[frame].userInfos)
		{
			if (!m_buffer[previousFrame].userInfos.contains(userInfo.first))
			{
				keysToBeDeleted.push_back(userInfo.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[frame].userInfos.erase(key);
		}
	}

	void SimulationBuffer::addAndUpdateUserInputs(int second, unsigned int previousFrame,
		unsigned int frame)
	{
		for (const std::pair<const int, Common::UserInfo>& previousUserInfo :
			m_buffer[previousFrame].userInfos)
		{
			if (!m_buffer[frame].userInfos.contains(previousUserInfo.first))
			{
				m_buffer[frame].userInfos.insert({previousUserInfo.first, Common::UserInfo
					{
						-1,
						previousUserInfo.second.input,
						Common::UserState{}
					}});
			}
			else if (m_buffer[frame].userInfos[previousUserInfo.first].second != second)
			{
				m_buffer[frame].userInfos[previousUserInfo.first].input =
					previousUserInfo.second.input;
			}
		}
	}

	void SimulationBuffer::updateScene(unsigned int previousFrame, unsigned int frame,
		const std::unordered_map<int, Common::UserInfo>& userInfos, bool hasStateFrame)
	{
		if (hasStateFrame)
		{
			m_buffer[frame].scene.updateWithStateFrame(m_buffer[previousFrame].scene, userInfos);
		}
		else
		{
			m_buffer[frame].scene.updateWithoutStateFrame(m_buffer[previousFrame].scene,
				userInfos);
		}
	}
};
