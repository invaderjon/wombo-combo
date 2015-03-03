#include "SubMesh.h"

using namespace graphics;

SubMesh::SubMesh() : 
	IIdentifiable(), mMaterial(), mIndices(GE_RES_INVALID)
{
}

SubMesh::SubMesh(Res indices, const Material& mat) : 
	IIdentifiable(), mIndices(indices), mMaterial(mat)
{
}

SubMesh::~SubMesh()
{
}

Res SubMesh::indices() const
{
	return mIndices;
}

void SubMesh::indices(Res ind)
{
	mIndices = ind;
}

const Material& SubMesh::material() const
{
	return mMaterial;
}

void SubMesh::material(const Material& mat)
{
	mMaterial = mat;
}
