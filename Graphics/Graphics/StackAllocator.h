#pragma once
#include <stack>
#include "Primitives.h"
#include "IAllocator.h"

namespace graphics
{
	class StackAllocator :
		public IAllocator < void* >
	{
	private:
		GEbyte*	mBlock;
		GEbyte*	mPos;
		memsize	mSize;
	public:
		StackAllocator(memsize size);
		~StackAllocator();

		// allocator methods
		void*	malloc(memsize msize);
		void	free(void* obj = NULL);
		void*	top();
		void	clear();
		memsize	size() const;
	};
}