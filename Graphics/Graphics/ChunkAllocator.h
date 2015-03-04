#pragma once
#include <list>
#include "IAllocator.h"

namespace graphics
{
	// Allocator that reserves memory in continguous chunks.
	// Best performance when sizeof(stored data) < chunk size - sizeof(uint)
	
	class ChunkAllocator :
		public IAllocator < void* >
	{
	private:
		// helper type
		typedef struct s_chunk
		{
			// number of blocks being used
			// [only meaningful for first chunk in continguous block]
			GEuint		chunks;
			// pointer to beginning of chunk
			GEbyte*		data;
			// number of available unused bytes for writing 
			// [only meaningful for last chunk in continguous block]
			GEuint		free;
			s_chunk() : chunks(0), data(NULL), free(0) { }
			s_chunk(GEuint count, void* dat) : chunks(count), data((GEbyte*)dat) { }
			s_chunk(void* dat, GEuint fre) : data((GEbyte*)dat), free(fre) { }

			inline bool operator==(const s_chunk& rhs)
			{
				return chunks == rhs.chunks && data == rhs.data && free == rhs.free;
			}

			friend inline bool operator== (const s_chunk& lhs, const s_chunk& rhs)
			{
				return lhs.chunks == rhs.chunks &&
					lhs.data == rhs.data == lhs.free == rhs.free;
			}
		} chunk;

		// instance
		GEbyte* mBlock;
		memsize mSize;
		memsize mChunkSize;
		std::list<chunk> mFree; // free chunk regions
		std::list<chunk> mTmp; // used chunks with space available for temp storage
		void add(const chunk& c); // adds a free chunk (keeps free chunks ordered)
		void merge(); // merges contiguous chunk regions
	public:
		ChunkAllocator(memsize chunkSize, GEuint chunks);
		~ChunkAllocator();

		void*	malloc(memsize size);		
		void*	malloc_tmp(memsize size);
		void	free(void* obj);
		memsize size();
	};

}