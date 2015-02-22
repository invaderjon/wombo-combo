#include "Buffers.h"

using namespace graphics;

GEuint Buffers::sNextBuf = 0;

GEuint Buffers::nextBuffer()
{
	return ++sNextBuf;
}