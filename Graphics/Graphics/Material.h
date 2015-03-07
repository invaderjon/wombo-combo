#pragma once

#include <IL/il.h>
#include "IResource.h"
#include "IIdentifiable.h"

namespace graphics
{
	class Material
		: public IIdentifiable
	{
	public:
		Material();
		~Material();

		virtual Res res() const;
		virtual GEuint state() const;
		virtual void state(GEuint state);
	};

}