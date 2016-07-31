#include "IOManager.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace Pixels2D;

bool IOManager::readFileToBuffer(const string &filePath, vector<unsigned char> &buffer)
{
	ifstream file(filePath, ios::binary);

	// error checking the path
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	// seek to the end
	file.seekg(0, ios::end);
	
	// get the file size
	int fileSize = file.tellg();
	file.seekg(0, ios::beg);

	// reduce the file size by any header bytes (if present)
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);

	file.close();

	return true;
}