#pragma once

#include "Primitives.h"

namespace graphics
{
	// memory block size
	typedef GEuint	memsize;

	// Interface which defines the general memory allocator type.
	// This interface is more functional as an identifier than providing methods.

	template<typename ptr>
	class IAllocator
	{
	public:		
		/// <summary>
		/// Allocates a region of memory with the specified size.
		/// </summary>
		/// <param name="msize">The size to allocate in bytes.</param>
		/// <returns>A pointer to the allocated memory block, returns NULL on failure.</returns>
		virtual ptr malloc(memsize msize) = 0;
		
		/// <summary>
		/// Frees the specified object.
		/// </summary>
		/// <param name="obj">A pointer to the region of memory.</param>
		virtual void free(ptr obj) = 0;
		
		/// <summary>
		/// Retrieves the size of the memory block the allocator is using.
		/// </summary>
		/// <returns>Allocated memory block size.</returns>
		virtual memsize size() const = 0;
	};

}

