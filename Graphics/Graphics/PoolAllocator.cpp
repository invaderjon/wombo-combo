#include "PoolAllocator.h"

using namespace graphics;

template<typename T>
PoolAllocator<T>::PoolAllocator(memsize count) 
	: mCount(count)
{
	mBlock = new T[count];
}

template<typename T>
PoolAllocator<T>::~PoolAllocator()
{
	// unallocate the block's resources
	delete mBlock;
}

template<typename T>
T* PoolAllocator<T>::malloc(memsize msize)
{
	// assert the block is of the proper size
	if (msize != sizeof(T))
		throw new std::runtime_error("Can only allocate memory blocks of specified type!");
	
	// if there are no more available blocks break
	if (mFree.empty())
		return NULL;

	// gets the next available block
	T* next = mFree.front();
	mFree.pop_front();
	return next;
}

template<typename T>
void PoolAllocator<T>::free(T* obj)
{
	// assert that the pointer lies within our memory block
	if (obj < mBlock || obj >= mBlock + mCount)
		throw new std::runtime_error("Attempted to free protected memory!");
	
	// re=add the item to the list
	mFree.push_back(T);
}

template<typename T>
memsize PoolAllocator<T>::size() const
{
	return mCount * sizeof(T);
}