#include "DSStackAllocator.h"

using namespace graphics;

DSStackAllocator::DSStackAllocator(memsize size)
	: mSize(size)
{
	// creates memory block
	mBlock = mTop = (GEbyte*)std::malloc(size);
	mBottom = mBlock + mSize;
}


DSStackAllocator::~DSStackAllocator()
{
	std::free(mBlock);
}

void* DSStackAllocator::malloc_top(memsize msize)
{
	// checks to make sure it won't overflow
	if (mTop + msize + sizeof(memsize) > mBottom)
		return NULL;

	// store the position
	void* pos = mTop;

	// increments by block size
	mTop += msize;

	// stores block size info
	*(memsize*)mTop = msize;
	
	// increments by size info size
	mTop += sizeof(memsize);

	return pos;
}

void* DSStackAllocator::malloc_bottom(memsize msize)
{
	// checks to make sure it won't overflow
	if (mBottom - msize - sizeof(memsize) < mTop)
		return NULL;

	// store the position
	void* pos = mBottom - msize;

	// decrements by block size and memsize
	mBottom -= msize + sizeof(memsize);

	// stores block size info
	*(memsize*)mBottom = msize;

	return pos;
}

void DSStackAllocator::free_top()
{
	// if already empty don't do anything
	if (mTop == mBlock)
		return;

	// frees first element in stack
	mTop -= sizeof(memsize);
	memsize size = *(memsize*)(mTop);
	mTop -= size;
}

void DSStackAllocator::free_bottom()
{
	// if already empty don't do anything
	if (mBottom = mBlock + mSize)
		return;

	// frees first element in stack
	memsize size = *(memsize*)(mBottom);
	mBottom += size + sizeof(memsize);
}

void* DSStackAllocator::top()
{
	// no need to offset if at the beginning of the block
	if (mTop == mBlock)
		return mTop;

	memsize size = *(memsize*)(mTop - sizeof(memsize));
	return mTop - sizeof(memsize) - size;
}

void* DSStackAllocator::bottom()
{
	// no need to offset if at the end of the block
	if (mBottom == mBlock + mSize)
		return mBottom;

	return mBottom + sizeof(memsize);
}

void DSStackAllocator::clear_top()
{
	mTop = mBlock;
}

void DSStackAllocator::clear_bottom()
{
	mBottom = mBlock + mSize;
}

void* DSStackAllocator::malloc(memsize size)
{
	return malloc_top(size);
}

void DSStackAllocator::free(void* obj)
{
	free_top();
}

memsize DSStackAllocator::size() const
{
	return mSize;
}