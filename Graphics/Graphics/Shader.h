#pragma once

#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "Primitives.h"
#include "Platform.h"

using namespace std;

namespace graphics
{
	class Shader
	{
	public:
		Shader();
		Shader(string path, GEint type);
		~Shader();
		GEuint id() const;
		void release();
	private:
		string loadFile(string path);
		GEuint mId;
	};
}

