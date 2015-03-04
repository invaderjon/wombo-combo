#pragma once
#include "IAllocator.h"

namespace graphics
{
	// doubled sided stack allocator
	class DSStackAllocator :
		public IAllocator < void* >
	{
	private:
		GEbyte* mBlock;
		GEbyte* mTop;
		GEbyte* mBottom;
		memsize mSize;
	public:
		DSStackAllocator(memsize size);
		~DSStackAllocator();

		// should be used by user
		void*		malloc_top(memsize msize);
		void*		malloc_bottom(memsize msize);
		void		free_top();
		void		free_bottom();
		void*		top();
		void*		bottom();
		void		clear_top();
		void		clear_bottom();

		// defaults to top of the stack
		void*	malloc(memsize size);
		void	free(void* obj = NULL);
	
		// gets size
		memsize	size() const;
	};

}