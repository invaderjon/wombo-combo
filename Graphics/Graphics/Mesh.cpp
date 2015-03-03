#include "Mesh.h"

using namespace graphics;

Mesh::Mesh()
	: IIdentifiable(), mVerts(GE_RES_INVALID), mSubMeshes(NULL)
{
}

Mesh::Mesh(Res verts, SubMesh* subMeshes)
	: IIdentifiable(), mVerts(verts), mSubMeshes(subMeshes)
{
}

Res Mesh::vertices() const
{
	return mVerts;
}

void Mesh::vertices(Res verts)
{
	mVerts = verts;
}

SubMesh* Mesh::submeshes() const
{
	return mSubMeshes;
}

void Mesh::submeshes(SubMesh* subs)
{
	mSubMeshes = subs;
}
