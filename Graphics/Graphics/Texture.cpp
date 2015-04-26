#include "Texture.h"
#include <IL/il.h>
#include <IL/ilu.h>

using namespace graphics;

Texture::Texture(string path, GEuint wrapMode, GEuint texId)
{
	// creates the image buffer
	ILuint imgId = 0;
	ilInit();
	ilGenImages(1, &imgId);
	ilBindImage(imgId);
	
	// loads the image
	ilLoadImage(path.c_str());

	// determines image size
	mWidth = ilGetInteger(IL_IMAGE_WIDTH);
	mHeight = ilGetInteger(IL_IMAGE_HEIGHT);
	
	// creates the raw data buffer
	mRawData = (GEubyte*)malloc(4 * sizeof(GEubyte) * mWidth * mHeight);
	
	// extracts pixels
	ilCopyPixels(0, 0, 0, mWidth, mHeight, 1, IL_RGBA, IL_UNSIGNED_BYTE, mRawData);

	// unbinds and deletes image from DevIL
	ilBindImage(0);
	ilDeleteImage(imgId);

	// creates texture
	mId = texId;
	glGenTextures(1, &mHandle);
	glBindTexture(GL_TEXTURE_2D, mHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mRawData);
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

GEubyte* Texture::raw() const
{
	return mRawData;
}

GEint Texture::width() const
{
	return mWidth;
}

GEint Texture::height() const
{
	return mHeight;
}