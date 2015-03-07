#include "Octree.h"

using namespace graphics;

// Octree

Octree::Octree(Vert* verts, Tri* faces, GEuint count)
	: Octree(verts, faces, count, Vec4(0, 0, 0, 1))
{
	
}

Octree::Octree(Vert* verts, Tri* faces, GEuint count, const Vec4& cube)
{
	mRoot = new OTLeaf(0, verts, faces, count, cube);
}

Octree::~Octree()
{
	// TODO: fix known memory leak here
	//free(mFaces);
}

// Leafs

OTLeaf::OTLeaf(GEuint depth, Vert* verts, Tri* faces, GEuint count, const Vec4& cube)
{
	// if it's already at the acceptable limit stop
	if (count <= GE_OCTREE_TRI_MAX || depth >= GE_OCTREE_DEPTH_MAX)
	{
		mCube = cube;
		mFaces = faces;
		mLeaves = NULL;
		mCount = count;
		return;
	}

	// allocates space for leaves
	mLeaves = (OTLeaf*)malloc(sizeof(OTLeaf) * 8);

	GEfloat offset = cube.w / 2;
	createLeaf(&mLeaves[0], depth + 1, verts, faces, count, Vec4(cube.x - offset, cube.y - offset, cube.z + offset, offset));
	createLeaf(&mLeaves[1], depth + 1, verts, faces, count, Vec4(cube.x - offset, cube.y + offset, cube.z + offset, offset));
	createLeaf(&mLeaves[2], depth + 1, verts, faces, count, Vec4(cube.x + offset, cube.y - offset, cube.z + offset, offset));
	createLeaf(&mLeaves[3], depth + 1, verts, faces, count, Vec4(cube.x + offset, cube.y + offset, cube.z + offset, offset));
	createLeaf(&mLeaves[4], depth + 1, verts, faces, count, Vec4(cube.x - offset, cube.y - offset, cube.z - offset, offset));
	createLeaf(&mLeaves[5], depth + 1, verts, faces, count, Vec4(cube.x - offset, cube.y + offset, cube.z - offset, offset));
	createLeaf(&mLeaves[6], depth + 1, verts, faces, count, Vec4(cube.x + offset, cube.y - offset, cube.z - offset, offset));
	createLeaf(&mLeaves[7], depth + 1, verts, faces, count, Vec4(cube.x + offset, cube.y + offset, cube.z - offset, offset));
}

GEboolean OTLeaf::cubeContains(const Vec3& pos, const Vec4& cube) const
{
	return (pos.x <= cube.x + cube.w && pos.x >= cube.x - cube.w) &&
		(pos.y <= cube.y + cube.w && pos.y >= cube.y - cube.w) &&
		(pos.z <= cube.z + cube.w && pos.z >= cube.z - cube.w);
}

GEboolean OTLeaf::cubeContains(Vert* verts, const Tri& face, const Vec4& cube) const
{
	return cubeContains(verts[face.a].position, cube) ||
		cubeContains(verts[face.b].position, cube) ||
		cubeContains(verts[face.c].position, cube);
}

void OTLeaf::createLeaf(OTLeaf* leaf, GEuint depth, Vert* verts, Tri* faces, GEuint count, const Vec4& cube) const
{
	// generates list of all faces inside of the cube
	vector<Tri> lfaces;
	for (GEuint i = 0; i < count; i++)
	{
		if (cubeContains(verts, faces[i], cube))
		{
			lfaces.push_back(faces[i]);
		}
	}

	// update 
	GEint fcount = lfaces.size();
	Tri* facearr = NULL;

	if (fcount > 0)
	{
		// copy face list to dynamic memory
		facearr = new Tri[fcount];
		facearr = (Tri*)memcpy(facearr, &lfaces[0], sizeof(Tri) * fcount);
	}

	*leaf = OTLeaf(depth, verts, facearr, fcount, cube);
}

void OTLeaf::append(vector<Vec3>& verts, vector<GEuint>& indices)
{
	// skip if it has children
	if (mLeaves != NULL)
	{
		mLeaves[0].append(verts, indices);
		mLeaves[1].append(verts, indices);
		mLeaves[2].append(verts, indices);
		mLeaves[3].append(verts, indices);
		mLeaves[4].append(verts, indices);
		mLeaves[5].append(verts, indices);
		mLeaves[6].append(verts, indices);
		mLeaves[7].append(verts, indices);
		return;
	}

	// gets the current size
	const int n = verts.size();

	// pushes back the vertices
	verts.push_back(Vec3(mCube.x - mCube.w, mCube.y - mCube.w, mCube.z - mCube.w));
	verts.push_back(Vec3(mCube.x + mCube.w, mCube.y - mCube.w, mCube.z - mCube.w));
	verts.push_back(Vec3(mCube.x + mCube.w, mCube.y + mCube.w, mCube.z - mCube.w));
	verts.push_back(Vec3(mCube.x - mCube.w, mCube.y + mCube.w, mCube.z - mCube.w));
	verts.push_back(Vec3(mCube.x - mCube.w, mCube.y - mCube.w, mCube.z + mCube.w));
	verts.push_back(Vec3(mCube.x + mCube.w, mCube.y - mCube.w, mCube.z + mCube.w));
	verts.push_back(Vec3(mCube.x + mCube.w, mCube.y + mCube.w, mCube.z + mCube.w));
	verts.push_back(Vec3(mCube.x - mCube.w, mCube.y + mCube.w, mCube.z + mCube.w));

	// appends indices
	indices.push_back(n + 0); indices.push_back(n + 1);
	indices.push_back(n + 1); indices.push_back(n + 2);
	indices.push_back(n + 2); indices.push_back(n + 3);
	indices.push_back(n + 3); indices.push_back(n + 0);
	indices.push_back(n + 4); indices.push_back(n + 5);
	indices.push_back(n + 5); indices.push_back(n + 6);
	indices.push_back(n + 6); indices.push_back(n + 7);
	indices.push_back(n + 7); indices.push_back(n + 4);
	indices.push_back(n + 0); indices.push_back(n + 4);
	indices.push_back(n + 1); indices.push_back(n + 5);
	indices.push_back(n + 2); indices.push_back(n + 6);
	indices.push_back(n + 3); indices.push_back(n + 7);
}

void Octree::push(Attributes& attrs)
{
	// clears buffers
	mVertices.clear();
	mIndices.clear();
	mRoot->append(mVertices, mIndices);

	// generates a vao
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// loads data
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vec3), &mVertices[0], GL_STATIC_DRAW);

	// enables attributes
	glVertexAttribPointer(attrs.position, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0);

	// enables attribtues
	glEnableVertexAttribArray(attrs.position);

	// loads indices
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GEuint), &mIndices[0], GL_STATIC_DRAW);
	
	// unbinds VAO
	glBindVertexArray(0);
}

void Octree::update(Mat4* view)
{
	// nothing to do here
	mModelMatrix = Mat4();
}

void Octree::render(ShaderIndices* indices)
{
	// updates matrices 
	glUniformMatrix4fv(indices->matrices.model, 1, GL_FALSE, glm::value_ptr(mModelMatrix));

	// draw cube
	glBindVertexArray(mVAO);
	glDrawElements(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}