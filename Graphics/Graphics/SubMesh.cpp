#include "SubMesh.h"

using namespace graphics;

SubMesh::SubMesh() : 
	IIdentifiable(), mMaterial(), mIndices(GE_RES_INVALID)
{
}

SubMesh::SubMesh(Res indices, Res mat) : 
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

Res SubMesh::material() const
{
	return mMaterial;
}

void SubMesh::material(Res mat)
{
	mMaterial = mat;
}
