#pragma once

#include "IIdentifiable.h"
#include "IResource.h"
#include "Texture.h"
#include "Material.h"

namespace graphics
{

	class SubMesh
		: public IIdentifiable
	{
	private:
		Res			mIndices;	// Index Data Resource Handle
		Res			mMaterial;	// Material

	public:
		SubMesh();
		SubMesh(Res indices, Res mat);
		~SubMesh();

		// accessors
		inline Res				indices() const;
		inline void				indices(Res ind);
		inline Res				material() const;
		inline void				material(Res mat);
	};

}
