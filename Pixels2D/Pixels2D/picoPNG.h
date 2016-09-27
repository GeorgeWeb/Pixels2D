#ifndef PICOPNG_HGUARD
#define PICOPNG_HGUARD
#ifdef PRAGMA_ONCE
	#pragma once
#endif

#include <vector>

namespace Pixels2D
{
	extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);
}

#endif // !PICOPNG_HGUARD