#include "Resources.h"

using namespace graphics;

Resources::Resources()
{
}

Resources::~Resources()
{
}

Material* Resources::loadMaterial(Res res)
{
	return loadMaterial(res, Options());
}

Material* Resources::loadMaterial(Res res, const Options& opts)
{
	return NULL;
}

Texture* Resources::loadTexture(Res res)
{
	return loadTexture(res, Options());
}

Texture* Resources::loadTexture(Res res, const Options& opts)
{
	return NULL;
}

Mesh* Resources::loadMesh(Res res)
{
	return loadMesh(res, Options());
}

Mesh* Resources::loadMesh(Res res, const Options& opts)
{
	return NULL;
}

Mesh* Resources::createMesh(GEuint vertexCount, SubMesh* submeshes)
{
	return NULL;
}

SubMesh* Resources::loadSubMesh(Res res)
{
	return loadSubMesh(res, Options());
}

SubMesh* Resources::loadSubMesh(Res res, const Options& opts)
{
	return NULL;
}

SubMesh* Resources::createSubMesh(GEuint indiceCount, const Material& material)
{
	return NULL;
}

Entity* Resources::loadEntity(Res res)
{
	return loadEntity(res, Options());
}

Entity* Resources::loadEntity(Res res, const Options& opts)
{
	return NULL;
}

Entity* Resources::createEntity(Mesh* mesh)
{
	return NULL;
}