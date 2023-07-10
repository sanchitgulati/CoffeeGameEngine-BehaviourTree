#pragma once
#include "../preprocessor/Common.h"
#include <string>
#include <map>

namespace Coffee {
	class PlayerPrefs_
	{
	private:
		std::map<std::string, std::string> _map;
	public:
		std::string getValue(std::string key,std::string defaultValue = "");
		void setValue(std::string key,std::string value);
		void write(std::string path);
		void read(std::string path);
	private:
		COFFEE_MAKE_SINGLETON(PlayerPrefs_);
	};
}
#define PlayerPrefs PlayerPrefs_::getInstance()
