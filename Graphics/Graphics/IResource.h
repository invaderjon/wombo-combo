#pragma once

#include "Primitives.h"

#define GE_RES_INVALID -1
#define UNLOADED 0
#define LOADING 1
#define LOADED 2
#define UNLOADING 3
//#define ERROR 4

namespace graphics
{

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
		/// Loads the specified data and processes it.
		/// </summary>
		/// <param name="data">The xml data.</param>
		/// <returns>Zero if successful or an error code.</returns>
		virtual GEuint load(GEbyte* data); // TODO: replace with psueudo xml loader class
	};

}

