#pragma once

#include "IIdentifiable.h"

namespace graphics
{
	class Material
		: public IIdentifiable, IResource
	{
	public:
		Material();
		~Material();
	};

}