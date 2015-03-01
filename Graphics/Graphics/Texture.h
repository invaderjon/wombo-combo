#pragma once
#include <cimg\CImg.h>
#include <string>
#include "Platform.h"
#include "Primitives.h"

using namespace std;
using namespace cimg_library;

namespace graphics
{

	class Texture
	{
	private:
		GEuint mId;
		GEuint mHandle;
	public:
		Texture(string path, GEuint wrapMode, GEuint tex);
		~Texture();

		GEuint handle();
		GEuint id();
	};

}