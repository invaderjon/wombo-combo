#pragma once

#include "Primitives.h"
#include "IResource.h"
#include "Texture.h"
#include "Mesh.h"
#include "Entity.h"
#include "Stream.h"

#define GE_RES_INVALID -1

namespace graphics
{

	typedef GEuint Res;

	// helper class
	class Options
	{

	};

	class Resources
	{
	public:
		Resources();
		~Resources();

		Material* loadMaterial(Res res);
		Material* loadMaterial(Res res, const Options& opts);
		Material* createMaterial(Texture* textures, GEuint texCount);

		Texture* loadTexture(Res res);
		Texture* loadTexture(Res res, const Options& opts);
		Texture* createTexture(GEuint width, GEuint height, GEuint format);
		Texture* createTextures(GEuint* widths, GEuint* heights, GEuint* format, GEuint count);

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

		/* Eventually implement
		// generic stream
		Stream* startStream(Res res);
		Stream* closeStream(Res res, const Options& opts);

		Stream* closeStream(Res res);
		*/

	};

}