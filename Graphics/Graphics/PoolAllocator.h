#pragma once
#include <list>
#include "IAllocator.h"

namespace graphics
{
	template<typename T>
	class PoolAllocator :
		public IAllocator < T* >
	{
	private:
		// pointer to memory block
		T* mBlock;
		memsize mCount;
		std::list<T*> mFree;
	public:
		PoolAllocator(memsize count);
		~PoolAllocator();

		// allocator methods
		T*		malloc(memsize msize = sizeof(T));
		void	free(T* obj);
		memsize	size() const;
	};
}
