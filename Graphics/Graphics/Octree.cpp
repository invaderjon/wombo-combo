#include "Octree.h"
#include "GraphicsEngine.h"

using namespace graphics;

// Octree

Octree::Octree()
	: Octree(Vec4(0, 0, 0, 1))
{
}

Octree::Octree(const Vec4& cube)
{
	mRoot = new OTLeaf(this, 0, cube);
}

Octree::~Octree()
{
	// TODO: fix known memory leak here
	//free(mFaces);
}


void Octree::push(Program* program)
{
	// clears buffers
	//mVertices.clear();
	//mIndices.clear();
	//mRoot->append(mVertices, mIndices);

	// generates a vao
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// loads data
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	//glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vec3), &mVertices[0], GL_STATIC_DRAW);

	// enables attributes
	glVertexAttribPointer(program->resource(VERT_POSITION), 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0);

	// enables attribtues
	glEnableVertexAttribArray(program->resource(VERT_POSITION));

	// loads indices
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GEuint), &mIndices[0], GL_STATIC_DRAW);

	// unbinds VAO
	glBindVertexArray(0);
}

void Octree::update(Mat4* view, GEdouble elapsed)
{
	// nothing to do here
	mModelMatrix = Mat4();
}

void Octree::render(Program* program)
{
	// updates matrices 
	glUniformMatrix4fv(program->resource(MAT_MODEL), 1, GL_FALSE, glm::value_ptr(mModelMatrix));

	// draw cube
	glBindVertexArray(mVAO);
	//glDrawElements(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

// Leafs

Octree::OTLeaf::OTLeaf(Octree* tree, GEuint depth, const Vec4& cube)
	: mLeafs(NULL), mFaces(), mOffsets(), mCube(cube), mDepth(depth)
{
	mTree = tree;
}

void Octree::OTLeaf::push(ID id, Tri* tris, GEint count, const VertData& data, const Mat4& trans)
{
	// if it exists already, clear the data before attempting to add it
	if (mOffsets.count(id))
		remove(id);
	
	// add the item
	add(id, tris, count, data, trans);
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

GEboolean Octree::OTLeaf::contains(const Vec3& posb, const Mat4& trans) const
{
	Vec3 pos = Vec3(Vec4(posb, 0) * trans);
	return (pos.x <= mCube.x + mCube.w && pos.x >= mCube.x - mCube.w) &&
		(pos.y <= mCube.y + mCube.w && pos.y >= mCube.y - mCube.w) &&
		(pos.z <= mCube.z + mCube.w && pos.z >= mCube.z - mCube.w);
}

GEboolean Octree::OTLeaf::contains(const VertData& data, const Tri& face, const Mat4& trans) const
{  
	Vec3* a = NULL;
	Vec3* b = NULL;
	Vec3* c = NULL;

	// calculates pointers based on architecture... MORE THAN A LITTLE DIRTY D:
	// TODO: figure out how to make this clean
	if (sizeof(void*) == sizeof(GEuint))
	{
		a = (Vec3*)(void*)((GEuint)data.data + (GEuint)data.offset + (GEuint)data.stride * + data.size * face.a);
		b = (Vec3*)(void*)((GEuint)data.data + (GEuint)data.offset + (GEuint)data.stride * + data.size * face.b);
		c = (Vec3*)(void*)((GEuint)data.data + (GEuint)data.offset + (GEuint)data.stride * + data.size * face.c);
	}
	else if (sizeof(void*) == sizeof(GEulong))
	{
		a = (Vec3*)(void*)((GEulong)data.data + (GEulong)data.offset + (GEulong)data.stride * +data.size * face.a);
		b = (Vec3*)(void*)((GEulong)data.data + (GEulong)data.offset + (GEulong)data.stride * +data.size * face.b);
		c = (Vec3*)(void*)((GEulong)data.data + (GEulong)data.offset + (GEulong)data.stride * +data.size * face.c);
	}

	return contains(*a, trans) || contains(*b, trans) || contains(*c, trans);
}