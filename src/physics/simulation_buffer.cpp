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
	void SimulationBuffer::setOwnInput(int second, unsigned int frame,
		const Common::UserInput& ownInput)
	{
		m_buffer[frame].mutex.lock();

		if (m_buffer[frame].userInfos.at(m_ownId).second != second)
		{
			m_buffer[frame].userInfos.at(m_ownId).input = ownInput;
			m_buffer[frame].userInfos.at(m_ownId).second = second;
		}

		m_buffer[frame].mutex.unlock();
	}

	void SimulationBuffer::update(int second, unsigned int frame)
	{
		unsigned int previousFrame = frame == 0 ? bufferSize - 1 : frame - 1;

		m_buffer[previousFrame].mutex.lock();
		m_buffer[frame].mutex.lock();

		updateUserInputs(second, previousFrame, frame);
		std::unordered_map<int, Common::UserInfo> userInfos = m_buffer[frame].userInfos;
		bool hasStateFrame = m_buffer[frame].hasStateFrame;
		m_buffer[frame].hasStateFrame = false;

		m_buffer[frame].mutex.unlock();
		m_buffer[previousFrame].mutex.unlock();

		updateScene(previousFrame, frame, userInfos, hasStateFrame);
	}

	void SimulationBuffer::updateUserInputs(int second, unsigned int previousFrame,
		unsigned int frame)
	{
		if (!m_buffer[frame].hasStateFrame)
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

			for (const std::pair<const int, Common::UserInfo>& previousUserInfo :
				m_buffer[previousFrame].userInfos)
			{
				if (m_buffer[frame].userInfos[previousUserInfo.first].second != second)
				{
					m_buffer[frame].userInfos[previousUserInfo.first].input =
						previousUserInfo.second.input;
				}
			}
		}
	}

	void SimulationBuffer::updateScene(unsigned int previousFrame, unsigned int frame,
		std::unordered_map<int, Common::UserInfo> userInfos, bool hasStateFrame)
	{
		if (hasStateFrame)
		{
			m_buffer[frame].scene->updateWithStateFrame(*m_buffer[previousFrame].scene, userInfos);
		}
		else
		{
			m_buffer[frame].scene->updateWithoutStateFrame(*m_buffer[previousFrame].scene,
				userInfos);
		}
	}
};
