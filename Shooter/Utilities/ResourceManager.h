#pragma once

#include <unordered_map>
#include <memory>

template <typename Resource>
class ResourceManager
{
	std::unordered_map<std::string, std::shared_ptr<Resource>> resources;

public:
	inline void add(std::string&& key, Resource* res) { resources[key] = std::shared_ptr<Resource>(res); }
	inline void remove(std::string&& key) { resources.erase(key); }
	inline Resource& operator[](const std::string& key) { return *resources[key]; }
	inline std::unordered_map<std::string, std::shared_ptr<Resource>>& getResources() { return resources; }
};