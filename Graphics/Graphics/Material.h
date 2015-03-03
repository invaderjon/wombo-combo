#pragma once

#include "IIdentifiable.h"

namespace graphics
{
	class Material
		: public IIdentifiable
	{
	public:
		Material();
		~Material();
	};

}