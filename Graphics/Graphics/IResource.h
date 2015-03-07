#pragma once

#include "Primitives.h"

#define GE_RES_INVALID -1
#define GE_RES_STATE_UNLOADED 0
#define GE_RES_STATE_LOADING 1
#define GE_RES_STATE_LOADED 2
#define GE_RES_STATE_UNLOADING 3

namespace graphics
{
	// type used to identify resources
	typedef GEuint Res;

	class IResource
	{
	public:		
		/// <summary>
		/// Retrieves the unique resource id.
		/// </summary>
		/// <returns>The unique id.</returns>
		virtual Res res() const;
		
		/// <summary>
		/// Retrieves the current resource state.
		/// </summary>
		/// <returns>The load state.</returns>
		virtual GEuint state() const;
		
		/// <summary>
		/// Updates the resource's current state.
		/// </summary>
		/// <param name="state">The load state.</param>
		virtual void state(GEuint state);
	};

}

