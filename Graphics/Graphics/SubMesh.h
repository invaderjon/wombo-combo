#pragma once

#include "Resources.h"
#include "Texture.h"
#include "Material.h"

namespace graphics
{

	class SubMesh
	{
	private:
		Res			mIndices;	// Index Data Resource Handle
		Material	mMaterial;	// Material

	public:
		SubMesh();
		SubMesh(Res indices, const Material& mat);
		~SubMesh();

		// accessors
		inline Res				indices() const;
		inline void				indices(Res ind);
		inline const Material&	material() const;
		inline void				material(const Material& mat);
	};

}
