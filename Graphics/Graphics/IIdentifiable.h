#pragma once
#include "Primitives.h"

#define GE_ID_INVALID -1

// Simple "interface" which provides a system for aquiring a globally unique
// id. This can also be used to avoid casts when checking for equality.
namespace graphics
{
	class IIdentifiable
	{
	public:				
		virtual ID id() const = 0;
		virtual void bind(ID id) = 0;
	};

}
