#pragma once

#include <vector>
#include "Graphics.h"
#include "Buffers.h"
#include "IRenderable.h"

#define GE_OCTREE_TRI_MAX 300
#define GE_OCTREE_DEPTH_MAX 3

namespace graphics
{
	using namespace std;

	class OTLeaf
	{
	public:
		OTLeaf(GEuint depth, Vert* verts, Tri* faces, GEuint count, const Vec4& cube);

		const Vec4& cube() const;

		// appends drawing information
		void append(vector<Vec3>& verts, vector<GEuint>& indices);
	private:
		// faces
		Tri* mFaces;
		// count
		GEuint mCount;
		// children
		OTLeaf* mLeaves;
		// cube size
		Vec4 mCube; // x, y, z, s (where s is side length / 2)
		// depth
		GEuint mDepth;

		// determines if a cube contains a triangle
		inline GEboolean cubeContains(const Vec3& pos, const Vec4& cube) const;

		// determines if a cube contains a triangle
		inline GEboolean cubeContains(Vert* verts, const Tri& face, const Vec4& cube) const;

		// creates new leaf
		void createLeaf(OTLeaf* leaf, GEuint depth, Vert* verts, Tri* faces, GEuint count, const Vec4& cube) const;
	};

	class Octree
		: IRenderable
	{

	private:
		OTLeaf* mRoot;
		vector<Vec3> mVertices;
		vector<GEuint> mIndices;

		void generateModel();
	public:
		Octree(Vert* verts, Tri* faces, GEuint faceCount);
		Octree(Vert* verts, Tri* faces, GEuint faceCount, const Vec4& cube);
		~Octree();

		void push(Attributes& attr);
		void update(Mat4* viewMatrix);
		void render(ShaderIndices* indices);
	};

}
