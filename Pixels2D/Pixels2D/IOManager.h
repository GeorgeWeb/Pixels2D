#ifndef IOMANAGER_HGUARD
#define IOMANAGER_HGUARD
#ifdef PRAGMA_ONCE
	#pragma once
#endif

#include <vector>

namespace Pixels2D
{
	class IOManager
	{
	public:
		static bool readFileToBuffer(const std::string &filePath, std::vector<unsigned char> &buffer);
	};
}

#endif // !IOMANAGER_HGUARD

