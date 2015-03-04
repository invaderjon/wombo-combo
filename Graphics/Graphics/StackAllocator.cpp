#include "StackAllocator.h"

using namespace graphics;


StackAllocator::StackAllocator(memsize size)
	: mSize(size)
{
	// creates the memory block
	mBlock = mPos = (GEbyte*)std::malloc(size);
}


StackAllocator::~StackAllocator()
{
	// free the data block
	std::free(mBlock);
}

void* StackAllocator::malloc(memsize msize)
{
	// checks to make sure it won't overflow
	if (mPos + msize + sizeof(memsize) > mBlock + mSize)
		return NULL;

	// store the position
	void* pos = mPos;

	// increments by block size
	mPos += msize;

	// stores block size info
	*(memsize*)mPos = msize;

	// increments by size info size
	mPos += sizeof(memsize);

	// return the position
	return pos;
}

void StackAllocator::free(void* obj)
{
	// if already empty don't do anything
	if (mPos == mBlock)
		return;

	// frees first element in stack
	mPos -= sizeof(memsize);
	memsize size = *(memsize*)(mPos);
	mPos -= size;
}

void* StackAllocator::top()
{
	// no need to offset if at the beginning of the block
	if (mPos == mBlock)
		return mPos;

	memsize size = *(memsize*)(mPos - sizeof(memsize));
	return mPos - sizeof(memsize) - size;
}

void StackAllocator::clear()
{
	// resets the position
	mPos = mBlock;
}

memsize StackAllocator::size() const
{
	return mSize;
}