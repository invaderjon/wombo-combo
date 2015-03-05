#pragma once

#include "IIdentifiable.h"
#include "Graphics.h"
#include "SubMesh.h"

// A simple class which is meant to hold all information regarding the
// vertices of a model.

namespace graphics
{
	class Mesh
		: public IIdentifiable
	{
	private:
		Res				mVerts;			// Vertex Data Resource Handle
		SubMesh*		mSubMeshes;		// Stores Info regarding the meshes
	public:
		Mesh();
		Mesh(Res verts, SubMesh* subMeshes);
		~Mesh();

		// accessors
		inline Res				vertices() const;
		inline void				vertices(Res verts);
		inline SubMesh*			submeshes()	const;
		inline void				submeshes(SubMesh* sub);
	};
}