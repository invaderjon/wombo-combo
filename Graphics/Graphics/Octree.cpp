#include "Octree.h"

using namespace graphics;

// Octree

Octree::Octree()
{
	mRoot = new OTLeaf(this, 0, Vec4(0, 0, 0, 1));
}

Octree::Octree(const Vec4& cube)
{
	mRoot = new OTLeaf(this, 0, cube);
}

Octree::~Octree()
{
	// TODO: fix known memory leak here
	//free(mLeafs);
}

void Octree::push(Program* program)
{
	// clears buffers
	mVertices.clear();
	mIndices.clear();

	// generates the buffers
	mRoot->build(mVertices, mIndices);

	// generates a vao
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// loads data
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vec3), &mVertices[0], GL_STATIC_DRAW);

	// enables attributes
	glVertexAttribPointer(program->resource(VERT_POSITION), 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0);

	// enables attribtues
	glEnableVertexAttribArray(program->resource(VERT_POSITION));

	// loads indices
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GEuint), &mIndices[0], GL_STATIC_DRAW);

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
	glDrawElements(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Octree::push(ID id, Tri* tris, Vert* verts, GEint count)
{
	mRoot->push(id, tris, verts, count);
}

GEint Octree::intersect(ID id, const Frustum& frustum, Tri* buffer)
{
	// use an unordered map to prevent duplicates
	//hash_map<GEint, Tri>& map = mBufferSet;
	
	// removes all items from the set
	//map.clear();

	// intersect with the octree
	return mRoot->intersect(id, frustum, buffer, /*map,*/ 0);
}