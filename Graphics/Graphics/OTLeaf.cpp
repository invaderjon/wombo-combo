#include "Octree.h"

using namespace graphics;

Octree::OTLeaf::OTLeaf(Octree* tree, GEuint depth, const Vec4& cube)
	: mTree(tree), mLeafs(NULL), mFaces(), mOffsets(), mDepth(depth), mCube(cube)
{	
}

const Vec4& Octree::OTLeaf::cube() const
{
	return mCube;
}

void Octree::OTLeaf::build(vector<Vec3>& verts, vector<GEuint>& indices)
{
	if (mLeafs == NULL)
	{
		// easy ref to the cube
		const Vec4& c = mCube;

		// adds verts
		verts.push_back(Vec3(c.x + c.w, c.y + c.w, c.z + c.w)); // size - 8
		verts.push_back(Vec3(c.x + c.w, c.y - c.w, c.z + c.w)); // size - 7
		verts.push_back(Vec3(c.x - c.w, c.y - c.w, c.z + c.w)); // size - 6
		verts.push_back(Vec3(c.x - c.w, c.y + c.w, c.z + c.w)); // size - 5
		verts.push_back(Vec3(c.x + c.w, c.y + c.w, c.z - c.w)); // size - 4
		verts.push_back(Vec3(c.x + c.w, c.y - c.w, c.z - c.w)); // size - 3
		verts.push_back(Vec3(c.x - c.w, c.y - c.w, c.z - c.w)); // size - 2
		verts.push_back(Vec3(c.x - c.w, c.y + c.w, c.z - c.w)); // size - 1

		// adds indices
		int i = verts.size();
		// first set
		indices.push_back(i - 8); // 8-7
		indices.push_back(i - 7);
		indices.push_back(i - 7); // 7-6
		indices.push_back(i - 6);
		indices.push_back(i - 6); // 6-5
		indices.push_back(i - 5);
		indices.push_back(i - 5); // 5-8
		indices.push_back(i - 8);
		// second set
		indices.push_back(i - 4); // 4-3
		indices.push_back(i - 3);
		indices.push_back(i - 3); // 3-2
		indices.push_back(i - 2);
		indices.push_back(i - 2); // 2-1
		indices.push_back(i - 1);
		indices.push_back(i - 1); // 1-4
		indices.push_back(i - 4);
		// sides
		indices.push_back(i - 8); // 8-4
		indices.push_back(i - 4);
		indices.push_back(i - 7); // 7-3
		indices.push_back(i - 3);
		indices.push_back(i - 6); // 6-2
		indices.push_back(i - 2);
		indices.push_back(i - 5); // 5-1
		indices.push_back(i - 1);
	}
	else
	{
		// if there are children call build on the children instead
		for (int i = 0; i < 8; ++i)
			mLeafs[i].build(verts, indices);
	}
}

void Octree::OTLeaf::intersect(ID id, const Frustum& frustum, unordered_set<Tri>& buffer)
{
	// if the cube doesn't contain the id stop
	if (!mOffsets.count(id))
		return;

	// stop if the frustum doesn't contain the cube
	if (!frustum.contains(mCube))
		return;

	// iterator variable
	int i;

	// if it has children intersect with the children
	if (mLeafs != NULL)
	{
		// intersect with each child
		for (i = 0; i < 8; ++i)
			mLeafs[i].intersect(id, frustum, buffer);

		// children will contain all the verts this does so stop
		return;
	}

	// otherwise push all children id's range
	OTRange range = mOffsets.at(id);
	Tri* tris = (&mFaces[0] + range.offset);
	for (i = 0; i < range.count; ++i)
		buffer.insert(tris[i]);
}

void Octree::OTLeaf::push(ID id, Tri* tris, GEint count, const VertData& data, const Mat4& trans)
{
	// if it exists already, clear the data before attempting to add it
	if (mOffsets.count(id))
		remove(id);

	// add the item
	add(id, tris, count, data, trans);
}

void Octree::OTLeaf::push(ID id, Tri* tris, Vert* verts, GEint count)
{
	// if it already exists, clear the data before attempting to add it
	if (mOffsets.count(id))
		remove(id);

	// add the item
	add(id, tris, verts, count);
}

void Octree::OTLeaf::add(ID id, Tri* tris, GEint count, const VertData& data, const Mat4& trans)
{
	vector<Tri> buffer;
	GEint contained = copyContained(buffer, tris, count, data, trans);

	// no vertices are contained in the this leaf so skip
	if (!contained)
		return;

	// check for errors
	if (contained < 0)
	{
		// TODO: handle error
		return;
	}

	// calculate and store the range
	const GEint ioffset = mFaces.size();
	const OTRange range(ioffset, contained, id);
	mOffsets[id] = range;

	// copies indices
	for (Tri tri : buffer)
		mFaces.push_back(tri);

	// determines growth
	GEint children = grow();

	// if it has children call add on all children
	if (children > 0)
	{
		// pushes the item to all the children
		//for (GEint i = 0; i < children; ++i)
		//	mLeafs[i].push(id, &mFaces[ioffset], contained, data, offset, stride, trans);
	}
}

void Octree::OTLeaf::add(ID id, Tri* tris, Vert* verts, GEint count)
{
	vector<Tri> buffer;
	GEint contained = copyContained(buffer, tris, verts, count);

	// no vertices are contained in the this leaf so skip
	if (!contained)
		return;

	// check for errors
	if (contained < 0)
	{
		// TODO: handle error
		return;
	}

	// calculate and store the range
	const GEint ioffset = mFaces.size();
	const OTRange range(ioffset, contained, id);
	mOffsets[id] = range;

	// copies indices
	for (Tri tri : buffer)
		mFaces.push_back(tri);

	// determines growth
	GEint children = grow();

	// if it has children call add on all children
	if (children > 0)
	{
		// pushes the item to all the children
		//for (GEint i = 0; i < children; ++i)
		//	mLeafs[i].push(id, &mFaces[ioffset], contained, data, offset, stride, trans);
	}
}

void Octree::OTLeaf::remove(ID id)
{
	// stores the range in a temp and removes it from the known ranges
	OTRange r(mOffsets[id]);
	mOffsets.erase(id);

	// removes all of the items from the vector associated with the item
	for (; r.count > 0; --r.count)
		mFaces.erase(mFaces.begin() + r.offset);
}

// TODO: pass all pre-existing items to the children
GEint Octree::OTLeaf::grow()
{
	// if it already has children return 8
	if (mLeafs != NULL)
		return 8;

	// check to make sure it meets the requirements for growth
	if (mDepth >= GE_OCTREE_DEPTH_MAX)
		return -1;
	else if (mFaces.size() <= GE_OCTREE_TRI_THRESHOLD)
		return -2;

	// if it does generate new leafs
	GEint i;
	GEint j;
	GEint k;
	GEfloat x;
	GEfloat y;
	GEfloat z;
	GEint index;
	Vec4 cube;
	const GEfloat w = mCube.w / 2;
	const GEint depth = mDepth + 1;

	// creates blank leafs
	mLeafs = new OTLeaf[8];

	// initializes leafs
	for (i = 0; i < 2; ++i) // x
	{
		for (j = 0; j < 2; ++j) // y
		{
			for (k = 0; k < 2; ++k) //z
			{
				// calculates cube index
				index = (i << 2) + (j << 1) + k;

				// calculates cube coordinates
				x = mCube.x + ((i ? -1 : 1) * w);
				y = mCube.y + ((j ? -1 : 1) * w);
				z = mCube.z + ((k ? -1 : 1) * w);

				// creates cube
				cube = Vec4(x, y, z, w);

				// initializes the leaf
				// TODO: pass all pre-existing items to the children
				mLeafs[index] = OTLeaf(mTree, depth, cube);
			}
		}
	}

	// return size
	return 8;
}

GEint Octree::OTLeaf::copyContained(vector<Tri>& buffer, Tri* tris, GEint count, const VertData& data, const Mat4& trans)
{
	GEint i;
	GEint j;
	for (i = 0, j = 0; i < count; ++i)
	{
		if (contains(data, tris[i], trans))
		{
			buffer.push_back(tris[i]);
			++j;
		}
	}
	return j;
}

GEint Octree::OTLeaf::copyContained(vector<Tri>& buffer, Tri* tris, Vert* verts, GEint count)
{
	GEint i;
	GEint j;
	for (i = 0, j = 0; i < count; ++i)
	{
		if (contains(verts, tris[i]))
		{
			buffer.push_back(tris[i]);
			++j;
		}
	}
	return j;
}

GEboolean Octree::OTLeaf::contains(const Vec3& posb, const Mat4& trans) const
{
	Vec3 pos = Vec3(Vec4(posb, 0) * trans);
	return (pos.x <= mCube.x + mCube.w && pos.x >= mCube.x - mCube.w) &&
		(pos.y <= mCube.y + mCube.w && pos.y >= mCube.y - mCube.w) &&
		(pos.z <= mCube.z + mCube.w && pos.z >= mCube.z - mCube.w);
}

GEboolean Octree::OTLeaf::contains(const Vec3& pos) const
{
	return (pos.x <= mCube.x + mCube.w && pos.x >= mCube.x - mCube.w) &&
		(pos.y <= mCube.y + mCube.w && pos.y >= mCube.y - mCube.w) &&
		(pos.z <= mCube.z + mCube.w && pos.z >= mCube.z - mCube.w);
}

// painfully generalized version
GEboolean Octree::OTLeaf::contains(const VertData& data, const Tri& face, const Mat4& trans) const
{
	Vec3* a = NULL;
	Vec3* b = NULL;
	Vec3* c = NULL;

	// calculates pointers based on architecture... MORE THAN A LITTLE DIRTY D:
	// TODO: figure out how to make this clean
	if (sizeof(void*) == sizeof(GEuint))
	{
		a = (Vec3*)(void*)((GEuint)data.data + (GEuint)data.offset + (GEuint)data.stride * +data.size * face.a);
		b = (Vec3*)(void*)((GEuint)data.data + (GEuint)data.offset + (GEuint)data.stride * +data.size * face.b);
		c = (Vec3*)(void*)((GEuint)data.data + (GEuint)data.offset + (GEuint)data.stride * +data.size * face.c);
	}
	else if (sizeof(void*) == sizeof(GEulong))
	{
		a = (Vec3*)(void*)((GEulong)data.data + (GEulong)data.offset + (GEulong)data.stride * +data.size * face.a);
		b = (Vec3*)(void*)((GEulong)data.data + (GEulong)data.offset + (GEulong)data.stride * +data.size * face.b);
		c = (Vec3*)(void*)((GEulong)data.data + (GEulong)data.offset + (GEulong)data.stride * +data.size * face.c);
	}

	return contains(*a, trans) || contains(*b, trans) || contains(*c, trans);
}

// friendly version
GEboolean Octree::OTLeaf::contains(Vert* verts, const Tri& face) const
{
	const Vec3& a = verts[face.a].position;
	const Vec3& b = verts[face.b].position;
	const Vec3& c = verts[face.c].position;
	return contains(a) || contains(b) || contains(c);
}
