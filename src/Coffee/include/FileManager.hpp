#pragma once
#include "../preprocessor/Common.h"
#include <string>
#include <map>

namespace Coffee {

	class FileManager_
	{
	public:
		std::string getData(std::string fileName);
		void setData(std::string fileName, std::string data);
		void setMapData(std::string fileName, std::map<std::string, std::string>& objRef);
		void getMapData(std::string fileName, std::map<std::string, std::string> &objRef);
	private:
		COFFEE_MAKE_SINGLETON(FileManager_);

	};

#define FileManager FileManager_::getInstance()
}