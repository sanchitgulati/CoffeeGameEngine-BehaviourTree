#include "../include/FileManager.hpp"
#include <iostream> 
#include <fstream> 

namespace Coffee {
    using namespace std;
	std::string FileManager_::getData(std::string fileName)
	{
        ifstream t;
        t.open(fileName.c_str(), ios::in);
        std::string str((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
        return str;

	}
    void FileManager_::setData(std::string fileName, std::string data)
    {
        ofstream file_obj;
        file_obj.open(fileName.c_str(), std::ofstream::out | std::ofstream::trunc);
        file_obj << data;
        file_obj.close();
    }
    void FileManager_::setMapData(std::string fileName, std::map<std::string, std::string>& objRef)
    {
        ofstream stream(fileName);
        for (auto& kv : objRef) {
            stream << kv.first;
            stream << "\n";
            stream << kv.second;
            stream << "\n";
        }
        stream.close();
    }
    void FileManager_::getMapData(std::string fileName, std::map<std::string, std::string>& objRef)
    {

        ifstream stream(fileName);
        string key;
        string value;
        while (std::getline(stream, key) && std::getline(stream, value)) {
            objRef[key] = value;
        }
        stream.close();
    }
}