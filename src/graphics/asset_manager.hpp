#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

template <typename Asset>
class AssetManager
{
public:
	AssetManager() = default;
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;
	std::shared_ptr<Asset> get(const std::string& path);
private:
	std::unordered_map<std::string, std::weak_ptr<Asset>> m_pool{};
};

template <typename Asset>
std::shared_ptr<Asset> AssetManager<Asset>::get(const std::string& path)
{
	auto iter = m_pool.find(path);
	if (iter != m_pool.end())
	{
		std::shared_ptr<Asset> asset = iter->second.lock();
		if (!asset)
		{
			asset = std::make_shared<Asset>(path);
			iter->second = asset;
		}
		return asset;
	}
	else
	{
		std::shared_ptr<Asset> asset = std::make_shared<Asset>(path);
		m_pool.insert(std::make_pair(path, asset));
		return asset;
	}
}
