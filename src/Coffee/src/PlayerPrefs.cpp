#include "../include/PlayerPrefs.hpp"
#include "../include/FileManager.hpp"

namespace Coffee {
	std::string PlayerPrefs_::getValue(std::string key, std::string defaultValue)
	{
		if (_map.find(key) != _map.end()) {
			return _map[key];
		}
		return defaultValue;
	}
	void PlayerPrefs_::setValue(std::string key, std::string value)
	{
		_map[key] = value;
	}
	void PlayerPrefs_::write(std::string path)
	{
		FileManager.setMapData(path,_map);
	}
	void PlayerPrefs_::read(std::string path)
	{
		FileManager.getMapData(path,_map);
	}
}