#pragma once

#include <unordered_map>
#include <memory>

template <typename T>
class ResourceManager
{
	std::unordered_map<std::string, std::shared_ptr<T>> resources;

public:
	inline void add(std::string&& key, T* res) { resources[key] = std::shared_ptr<T>(res); }
	inline void remove(std::string&& key) { resources.erase(key); }
	inline T& operator[](const std::string& key) { return *resources[key]; }
	inline std::unordered_map<std::string, std::shared_ptr<T>>& getResources() { return resources; }
};