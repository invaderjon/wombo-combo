#pragma once

#include "Graphics.h"
#include "Resources.h"
#include "SubMesh.h"

// A simple class which is meant to hold all information regarding the
// vertices of a model.

namespace graphics
{
	class Mesh
	{
	private:
		// global
		static GEuint sCurId;
		static GEuint nextId();

		// instance
		GEuint			mId;			// Unique ID
		Res				mVerts;			// Vertex Data Resource Handle
		SubMesh*		mSubMeshes;		// Stores Info regarding the meshes
		
		// TODO: implement with resource manager
		//Resources* res;
		//GEuint mDataHandle; // handle that points to data
	public:
		Mesh();
		~Mesh();

		// accessors
		inline GEuint			id() const;
		inline Res				vertices() const;
		inline void				vertices(Res verts);
		inline SubMesh*			submeshes()	const;
		inline void				submeshes(SubMesh* sub);
	};
}