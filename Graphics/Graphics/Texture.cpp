#include "Texture.h"

using namespace graphics;

Texture::Texture(string path, GEuint wrapMode, GEuint texId)
{
	CImg<unsigned char> img(path.c_str());
	unsigned char* data = (unsigned char*)malloc(3 * sizeof(unsigned char) * img.width() * img.height());

	// converts cimg's planar representation to rgb representation
	for (int y = 0; y < img.height(); y++)
	{
		for (int x = 0; x < img.width(); x++)
		{
			int px = 3 * x;
			data[y * img.width() * 3 + px] = img(x, y, 0, 0);
			data[y * img.width() * 3 + px + 1] = img(x, y, 0, 1);
			data[y * img.width() * 3 + px + 2] = img(x, y, 0, 2);
		}
	}

	// creates texture
	mId = texId;
	glGenTextures(1, &mHandle);
	glBindTexture(GL_TEXTURE_2D, mHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img.width(), img.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);

	// release the memory
	//free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mId);
}

GEuint Texture::handle() const
{
	return mHandle;
}

GEuint Texture::id() const
{
	return mId;
}