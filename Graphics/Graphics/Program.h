#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "Platform.h"
#include "Shader.h"
#include "UniformBlock.h"

#define VERT_POSITION "vPosition"
#define VERT_NORMAL "vNormal"
#define MAT_MODEL "mModel"
#define MAT_VIEW "mView"
#define MAT_PROJECTION "mProjection"
#define MAT_NORMAL "mNormal"

#define GE_PROGRAM_INTROSPECTION_INPUTS 1
#define GE_PROGRAM_INTROSPECTION_UNIFORMS 2
#define GE_PROGRAM_INTROSPECTION_UNIFORM_BLOCKS 3

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
		const UniformBlock& block(const string& name) const;
	private:
		GEuint mId;
		unordered_map<string, GEint> mResources;
		unordered_map<string, UniformBlock> mUniformBlocks;

		// extracts all of the resources for the program
		void extract();
		// extracts a resource of a sepcified type
		void extractResources(GEenum type);
	};
}

