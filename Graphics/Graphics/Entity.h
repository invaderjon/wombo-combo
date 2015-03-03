#pragma once
#include "Graphics.h"
#include "Node.h"
#include "Mesh.h"

// Defines anything that can rendered within the world

namespace graphics
{
	class Entity :
		public Node
	{
	private:
		Mesh* mMesh;
		Vec3 mPositon;
		Vec4 mScale;
		Quat mRotation;
	public:
		Entity();
		Entity(Mesh* mesh);
		~Entity();

		// gets/sets mesh
		inline Mesh* mesh() const;
		inline void mesh(Mesh* mes);

		// gets/sets position
		inline const Vec3& position() const;
		inline void position(const Vec3& pos);

		// gets/sets scale
		inline const Vec4& scale() const;
		inline void scale(const Vec4& sca);

		// gets/sets rotation
		inline const Quat& rotation() const;
		inline void rotation(const Quat& rot);
	};
}