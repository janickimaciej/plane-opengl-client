#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

namespace Graphics
{
	template <typename Key, typename Asset>
	class AssetManager
	{
	public:
		AssetManager() = default;
		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		std::shared_ptr<Asset> get(const Key& key);

	private:
		std::unordered_map<Key, std::weak_ptr<Asset>> m_pool{};
	};

	template <typename Key, typename Asset>
	std::shared_ptr<Asset> AssetManager<Key, Asset>::get(const Key& key)
	{
		auto iter = m_pool.find(key);
		if (iter != m_pool.end())
		{
			std::shared_ptr<Asset> asset = iter->second.lock();
			if (!asset)
			{
				asset = std::make_shared<Asset>(key);
				iter->second = asset;
			}
			return asset;
		}
		else
		{
			std::shared_ptr<Asset> asset = std::make_shared<Asset>(key);
			m_pool.insert({key, asset});
			return asset;
		}
	}
};
