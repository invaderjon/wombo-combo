#pragma once
#include "Primitives.h"

#define GE_ID_INVALID -1

// Simple "interface" which provides a system for aquiring a globally unique
// id. This can also be used to avoid casts when checking for equality.
namespace graphics
{
	// id type
	typedef GEuint ID;

	class IIdentifiable
	{
	private:
		// globla
		static ID sCurId;		
		static ID nextId();

		// instance
		ID mId;
	public:
		IIdentifiable();
		~IIdentifiable();
				
		inline virtual ID id() const;
	};

}
