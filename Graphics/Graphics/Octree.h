#pragma once

#include <unordered_map>
#include <vector>
#include <list>
#include "Graphics.h"
#include "Buffers.h"
#include "IRenderable.h"
#include "Program.h"
#include "Frustum.h"

#define GE_OCTREE_TRI_THRESHOLD 10
#define GE_OCTREE_DEPTH_MAX 100

namespace graphics
{
	using namespace std;

	class GraphicsEngine;

	class Octree
		: IRenderable
	{

	private:
		//
		// nested structs
		//

		typedef struct	sOTRange
		{
			GEint		offset;
			GEint		count;
			ID			id;
			sOTRange() : offset(-1), count(-1), id(GE_ID_INVALID) { }
			sOTRange(GEint start, GEint number, ID Id) : offset(start), count(number), id(Id) { }
		}				OTRange;

		//
		// nested classes
		//

		class OTLeaf
		{
		public:
			// uninitialied leaf
			OTLeaf() : mLeafs(NULL), mTree(NULL), mDepth(-1), mCube(-1), mFaces(), mOffsets() { }

			// sets up a basic leaf
			OTLeaf(Octree* tree, GEuint depth, const Vec4& cube);

			// gets the vector that describes the leaf's binding cube
			const Vec4& cube() const;

			// builds the octree model
			void build(vector<Vec3>& verts, vector<GEuint>& indices);

			// intersects the octree with the given frustum
			void intersect(ID id, const Frustum& frustum, unordered_map<GEint, Tri>& buffer);

			// pushes an item to the leaf (assumes that the points each contain at least 3 floats)
			// this is the only method that should be called by the octree
			void push(ID id, Tri* tris, GEint count, const VertData& data, const Mat4& trans);

			// easier push since I never got around to generalizing objects
			void push(ID id, Tri* tris, Vert* verts, GEint count);
		private:
			// octree reference (for getting vertex information)
			Octree* mTree;
			// indices (as triples in the forms of Tris)
			vector<Tri> mFaces;
			// object offsets (to go from id to offset)
			unordered_map<ID, OTRange> mOffsets;
			// children
			OTLeaf* mLeafs;
			// cube size
			Vec4 mCube; // x, y, z, s (where s is side length / 2)
			// depth
			GEuint mDepth;
			// adds an item to the list
			void add(ID id, Tri* tris, GEint count, const VertData& data, const Mat4& trans);
			// adds an item to the list
			void add(ID id, Tri* tris, Vert* verts, GEint count);

			// clears all the data regarding a given id
			void remove(ID id);

			// TODO: pass all pre-existing items to the children (need to figure out a way to get access to the data)
			// creates children [if necessary] and returns the number of children or error
			GEint grow();

			// copies all items that are inside this leaf to a buffer, returns number contained or error
			GEint copyContained(vector<Tri>& buffer, Tri* tris, GEint count, const VertData& data, const Mat4& trans);

			// copies all items that are inside this leaf to a buffer, returns number contained or error
			GEint copyContained(vector<Tri>& buffer, Tri* tris, Vert* verts, GEint count);

			// determines if a cube contains a triangle
			inline GEboolean contains(const Vec3& pos, const Mat4& trans) const;

			// determines if a cube contains a triangle
			inline GEboolean contains(const Vec3& pos) const;

			// determines if a cube contains a triangle
			inline GEboolean contains(const VertData& data, const Tri& face, const Mat4& trans) const;

			// determines if a cube contains a triangle
			inline GEboolean contains(Vert* vert, const Tri& face) const;
		};

		//
		// instance
		//

		// root node
		OTLeaf* mRoot;

		// debug vertices
		vector<Vec3> mVertices;

		// debug indices
		vector<GEuint> mIndices;

		// Used by intersect to avoid reallocating memory
		// for a set every time the function is called.		
		//
		// Although it might be a slight memory pit it's probably
		// better to have a giant structure in memory than to have to
		// reallocate and deallocate the structure every frame.
		// More importantly: It lets me not have to modify existing code which
		//                   I don't have time to finish. (final exams)
		//
		// TODO: Clean this up, implement an easy Tri hashing function and manually track
		//       whether or not the vertex is already in the buffer.
		unordered_map<GEint, Tri> mBufferSet;

		void generateModel();
	public:
		Octree();
		Octree(const Vec4& cube);
		~Octree();

		void push(Program* program);
		void update(Mat4* viewMatrix, GEdouble elapsed);
		void render(Program* program);
		void push(ID id, Tri* tris, Vert* verts, GEint count);

		// intersects an item in the octree with the frustum
		void intersect(ID id, const Frustum& frustum, vector<Tri>& buffer);
	};
}
