#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "Platform.h"
#include "Shader.h"

#define VERT_POSITION "vPosition"
#define VERT_NORMAL "vNormal"
#define MAT_MODEL "mModel"
#define MAT_VIEW "mView"
#define MAT_PROJECTION "mProjection"
#define MAT_NORMAL "mNormal"

using namespace std;

namespace graphics
{
	class Program
	{
	public:
		Program(Shader* shaders, GEuint count);
		~Program();
		void bind() const;
		void unbind() const;
		GEuint id() const; 
		// gets resource via name in shader
		GEint resource(const string& name) const;
	private:
		GEuint mId;
		unordered_map<string, GEint> mResources;

		// extracts all of the resources for the program
		void extract();
		// extracts a resource of a sepcified type
		void extractResources(GEenum type);
	};
}

