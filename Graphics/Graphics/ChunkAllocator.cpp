#include "ChunkAllocator.h"

using namespace graphics;

ChunkAllocator::ChunkAllocator(memsize chunkSize, GEuint chunks)
	: mSize(chunkSize*chunks), mChunkSize(chunkSize), mFree(), mTmp()
{
	if (chunkSize < sizeof(GEuint))
		throw new std::runtime_error("Chunk size must be large enough to hold size data!");

	// allocate the memory block
	mBlock = (GEbyte*)std::malloc(chunkSize*chunks);

	// add the initial chunk
	mFree.push_back(chunk(chunks, mBlock));
}

ChunkAllocator::~ChunkAllocator()
{
	std::free(mBlock);
}

/// <summary>
/// Mallocs the specified msize.
/// </summary>
/// <param name="msize">The msize.</param>
/// <returns></returns>
void* ChunkAllocator::malloc(memsize msize)
{
	// calculates padded size
	GEuint psize = msize + sizeof(memsize);

	chunk c;
	// iterates through free blocks to search for space
	for (auto iter = mFree.begin();
		iter != mFree.end();
		++iter)
	{
		// finds a chunk block while minimizing the number of unused chunks [helps reduce fragmenting]
		if (psize < (*iter).chunks * mChunkSize && (c.chunks == 0 || (*iter).chunks < c.chunks))
		{
			c = (*iter);
		}
	}

	// no appropriately sized chunk could be found.
	if (c.chunks == 0)
		return NULL;

	// calculates the number of extra bytes that will remain
	GEuint extra = (mChunkSize - (psize % mChunkSize)) % mChunkSize;

	// calculates number of chunks necessary
	GEuint chunks = (psize + extra) / mChunkSize;

	// calculates the number of chunks that will remain
	GEuint rem = c.chunks - chunks;

	// used chunk
	chunk used = chunk(chunks, c.data, extra);

	// removes the old chunk
	mFree.remove(c);

	// determines if there are left over chunks
	if (rem > 0)
	{
		// free chunk
		GEbyte* offset = c.data + (chunks * mChunkSize);
		chunk fchunk = chunk(rem, offset);
		add(fchunk);
	}

	// determines if there is extra memory to use
	if (extra > 0)
	{
		GEbyte* offset = c.data + (mChunkSize * (used.chunks - 1));
		chunk tmp = chunk(offset, extra);
		mTmp.push_back(tmp);
	}
	
	// writes meta data to used chunk
	*(memsize*)used.data = msize;

	// returns pointer to usable data block
	return used.data + sizeof(memsize);
}

/// <summary>
/// Allocates temporary a block of memory within an allocated chunk.
/// </summary>
/// <warning>
/// The allocated memory will be freed when the enacasing chunk is released.
/// </warning>
/// <param name="size">The memory block size.</param>
/// <returns>A pointer to the region in memory, or NULL if no available memory could be found.</returns>
void* ChunkAllocator::malloc_tmp(memsize msize)
{
	// impossible to have a tmp block larger than a chunk
	if (msize > mChunkSize)
		throw new std::runtime_error("Temp size cannot be larger than the block size!");
	
	// iterates through allocated blocks to search for space
	chunk* c = NULL;
	for (auto iter = mTmp.begin();
		iter != mTmp.end();
		++iter)
	{
		// finds a block that fits while minimizing remaining bytes
		if (msize < (*iter).free && (c == NULL || (*iter).free < c->free))
		{
			c = &(*iter);
		}
	}

	// no free memory could be found
	if (c == NULL)
		return NULL;

	// calculates the free region
	GEbyte* reg = static_cast<GEbyte*>(c->data) + mChunkSize - c->free;
	
	// updates the remaining free blocks
	c->free -= msize;

	// returns the pointer to the free region
	return reg;
}

void ChunkAllocator::free(void* obj)
{
	// make sure the memory location lies within the memory block
	if (obj < mBlock || obj >= mBlock + mSize)
		throw new std::runtime_error("Attempting to access private memory!");

	// extracts size info
	void* ptr = (GEbyte*)obj - sizeof(memsize);
	memsize msize = *(memsize*)(ptr);
	memsize psize = msize + sizeof(memsize);
	memsize extra = (mChunkSize - (psize % mChunkSize)) % mChunkSize;
	memsize used = psize + extra;
	memsize chunks = used / mChunkSize;

	// determines which chunk region is being released
	chunk c = chunk(chunks, ptr);

	// remove the tmp block if it exists
	if (extra > 0)
	{
		GEbyte* offset = c.data + (mChunkSize * (c.chunks - 1));
		chunk tmp = chunk(offset, extra);
		mTmp.remove(tmp);
	}

	// adds chunk to free
	add(c);

	// merges contiguous free regions
	merge();
}

void ChunkAllocator::add(const chunk& c)
{
	// adds chunk to list of free chunks in order of position in memory
	auto iter = mFree.begin();
	for (;
		iter != mFree.end() && c.data > (*iter).data;
		++iter)
		;
	// inserts the item
	mFree.insert(iter, c);
}

void ChunkAllocator::merge()
{
	// search for contiguous regions
	int contiguous = 0;
	auto x = mFree.begin();
	auto y = mFree.begin();
	if (y != mFree.end())
		y++;

	// so long as we haven't finished checkking continue
	while (y != mFree.end())
	{
		// checks to see if they're contiguous
		contiguous = ((*x).data + ((*x).chunks * mChunkSize)) == (*y).data;

		// if they were contiguous merge them and
		if (contiguous)
		{
			// merge two regions
			(*x).chunks += (*y).chunks;

			// remove second region
			y = mFree.erase(y);
		}
		else // neither were contiguous so just move on
		{
			x++;
			y++;
		}
	}
}

memsize ChunkAllocator::size() const
{
	return mSize;
}