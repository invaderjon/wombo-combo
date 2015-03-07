#pragma once

#include <IL\il.h>
#include "Primitives.h"
#include "ChunkAllocator.h"
#include "ResourceDb.h"
#include "IResource.h"
#include "Texture.h"
#include "Mesh.h"
#include "Entity.h"
#include "Stream.h"

#define GE_RES_INVALID -1

namespace graphics
{
	// helper class
	struct Options
	{
		// force immediate loading
		GEboolean immediate;

		Options() : immediate(1) { }
	};

	class Resources
	{
	private:
		// methods
		// converts respath to filepath
		string parseResPath(string path) const;

		// variables
		ChunkAllocator alloc;
		ResourceDb mDB;
	public:
		Resources();
		~Resources();

		Material* loadMaterial(Res res);
		Material* loadMaterial(Res res, const Options& opts);

		Texture* loadTexture(Res res);
		Texture* loadTexture(Res res, const Options& opts);

		Mesh* loadMesh(Res res);
		Mesh* loadMesh(Res res, const Options& opts);
		Mesh* createMesh(GEuint vertexCount, SubMesh* submeshes);

		SubMesh* loadSubMesh(Res res);
		SubMesh* loadSubMesh(Res res, const Options& opts);
		SubMesh* createSubMesh(GEuint indiceCount, const Material& material);
		SubMesh* createSubMeshes(GEuint* indiceCounts, Material* materials, GEuint count);

		Entity* loadEntity(Res res);
		Entity* loadEntity(Res res, const Options& opts);
		Entity* createEntity(Mesh* mesh);

		/* TODO: implement
		// generic stream
		Stream* startStream(Res res);
		Stream* closeStream(Res res, const Options& opts);

		Stream* closeStream(Res res);
		*/

	};

}