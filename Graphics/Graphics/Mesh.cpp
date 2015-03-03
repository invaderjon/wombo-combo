#include "Mesh.h"

using namespace graphics;

GEuint Mesh::sCurId = -1;

Mesh::Mesh() : mId(nextId()), mVerts(GE_RES_INVALID)
{
}

Mesh::~Mesh()
{
}

GEuint Mesh::id() const
{
	return mId;
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

GEuint Mesh::nextId()
{
	return ++sCurId;
}