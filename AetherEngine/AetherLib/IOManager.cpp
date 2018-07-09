#include "IOManager.h"

#include <fstream>
namespace Aether
{
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary); //std::ios::binary means we're reading the file entirely in binary
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		//Using seekg and tellg is assuming the person using this doesn't know how big their file size is
		//Seek ot the end of the faile
		file.seekg(0, std::ios::end); //Seekg would take our filepointer, which is how we're reading the file, and moves to the end of the file

		//Get the file size
		int fileSize = file.tellg(); //returns an integar that says how many bytes are before the current location
		file.seekg(0, std::ios::beg);

		//Reduce the file size by any header bytes that might be present. This probably doesn't matter, but better safe than sorry.
		fileSize -= file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize); //Get the first element in buffers, fileSize is how many bytes we want to read to buffer.
		file.close();

		return true;

	}
}
