#pragma once
#include <string>
#include "Platform.h"
#include "Primitives.h"

using namespace std;

namespace graphics
{

	class Texture
	{
	private:
		GEuint	mId;
		GEuint	mHandle;
		GEubyte* mRawData;
		GEint mWidth;
		GEint mHeight;
	public:
		Texture(string path, GEuint wrapMode, GEuint tex);
		~Texture();

		GEuint handle() const;
		GEuint id() const;
		GEubyte* raw() const;
		GEint width() const;
		GEint height() const;
	};

}