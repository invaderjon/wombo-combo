#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include "Platform.h"
#include "Shader.h"

using namespace std;

namespace graphics
{
	class Program
	{
	public:
		Program(Shader* shaders, GEuint count);
		~Program();
		GEuint id() const;
	private:
		GEuint mId;
	};
}

