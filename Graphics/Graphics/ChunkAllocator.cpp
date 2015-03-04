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
	mFree.push_back(chunk(mBlock, chunks));
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
	GEuint psize = msize + sizeof(GEuint);

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
	GEuint extra = psize % mChunkSize;

	// calculates number of chunks necessary
	GEuint chunks = (psize + extra) / mChunkSize;

	// calculates the number of chunks that will remain
	GEuint rem = c.chunks - chunks;

	// used chunk
	chunk used = chunk(chunks, c.data);

	// removes the old chunk
	mFree.remove(c);

	// determines if there are left over chunks
	if (rem > 0)
	{
		// free chunk
		GEbyte* offset = c.data + (chunks * mChunkSize);
		chunk fchunk = chunk(rem, offset);
		mFree.push_back(fchunk);
	}

	// determines if there is extra memory to use
	if (extra > 0)
	{
		GEbyte* offset = c.data + (mChunkSize + (used.chunks - 1));
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
	chunk c;
	for (auto iter = mTmp.begin();
		iter != mTmp.end();
		++iter)
	{
		// finds a block that fits while minimizing remaining bytes
		if (msize < (*iter).free && (c.free == 0 || (*iter).free < c.free))
		{
			c = (*iter);
		}
	}

	// no free memory could be found
	if (c.free = NULL)
		return NULL;

	// calculates the free region
	GEbyte* reg = static_cast<GEbyte*>(c.data);
	reg = reg + mChunkSize - c.free;
	
	// updates the remaining free blocks
	c.free -= msize;

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
	memsize padded = msize + sizeof(memsize);
	memsize used = padded + (padded % mChunkSize);
	memsize chunks = used / mChunkSize;

	// determines which chunk region is being released
	chunk c = chunk(chunks, ptr);

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
		c.data > (*iter).data && iter != mFree.end();
		++iter)
		;
	// inserts the item
	mFree.insert(iter, c);
}

void ChunkAllocator::merge()
{
	int merged = 0;

	// merges all contiguous blocks of memory
	do
	{
		// search for contiguous regions
		int contiguous = 0;
		auto c1 = mFree.begin();
		auto c2 = mFree.begin();
		c2++;
		for (; c2 != mFree.end() && !contiguous; ++c1, ++c2)
		{
			// checks to see if they're contiguous
			contiguous = ((*c1).data + ((*c1).chunks * mChunkSize)) == (*c2).data;
		}

		if (contiguous)
		{
			// merge two regions
			(*c1).chunks += (*c2).chunks;

			// remove second region
			mFree.remove(*c2);
		}

		// update merged
		merged = contiguous;
	} while (merged);
}

memsize ChunkAllocator::size()
{
	return mSize;
}