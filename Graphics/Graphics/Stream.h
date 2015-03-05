#pragma once
#include "IResource.h"

namespace graphics
{

	class Stream :
		public IResource
	{
	public:
		Stream();
		~Stream();
	};

}