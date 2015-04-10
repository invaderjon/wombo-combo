#include "IcoSphere.h"

using namespace graphics;

IcoSphere::IcoSphere(GEfloat radius, GEint subdivisions) 
	: mRadius(radius), mSubdivisions(subdivisions)
{
	initialize();
}

IcoSphere::~IcoSphere()
{
}

// public

void IcoSphere::push(Program* program)
{
	mVAO = Buffers::nextBuffer();
	mVBO = Buffers::nextBuffer();
	mIBO = Buffers::nextBuffer();

	// generates a vao
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// loads data
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vert), &mVertices[0], GL_STATIC_DRAW);

	// set attributes
	glVertexAttribPointer(program->resource(VERT_POSITION), 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);
	glVertexAttribPointer(program->resource(VERT_NORMAL), 3, GL_FLOAT, GL_TRUE, sizeof(Vert), (void*)(3 * sizeof(GEfloat)));

	// enables attributes
	glEnableVertexAttribArray(program->resource(VERT_POSITION));
	glEnableVertexAttribArray(program->resource(VERT_NORMAL));

	// load indices
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mFaces.size() * sizeof(Tri), &mFaces[0], GL_STATIC_DRAW);

	// unbinds VAO
	glBindVertexArray(0);
}

void IcoSphere::update(Mat4* viewMatrix, GEdouble elapsed)
{
	mModelMatrix = Mat4();
	mModelMatrix[0][0] = mModelMatrix[1][1] = mModelMatrix[2][2] = mModelMatrix[3][3] = 1.0f;
	Mat3 modelView = Mat3(mModelMatrix * *viewMatrix);
	mNormalMatrix = glm::inverseTranspose(modelView);
}

void IcoSphere::render(Program* program)
{
	// updates matrices
	glUniformMatrix4fv(program->resource(MAT_MODEL), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
	glUniformMatrix3fv(program->resource(MAT_NORMAL), 1, GL_FALSE, glm::value_ptr(mNormalMatrix));

	// draw height map
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, mFaces.size() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

GEfloat IcoSphere::radius() const
{
	return mRadius;
}

GEint IcoSphere::subdivisions() const
{
	return mSubdivisions;
}

// private

void IcoSphere::initialize()
{
	// creates 12 verts
	GEfloat t = (1.0 + sqrtf(5.0f)) / 2.0;
	
	GEint n = 0;
	Vec3 verts[12];
	
	// first set
	verts[n++] = Vec3(-1,  t,  0); // p0
	verts[n++] = Vec3( 1,  t,  0); // p1
	verts[n++] = Vec3(-1, -t,  0); // p2
	verts[n++] = Vec3( 1, -t,  0); // p3
	// second set
	verts[n++] = Vec3( 0, -1,  t); // p4
	verts[n++] = Vec3( 0,  1,  t); // p5
	verts[n++] = Vec3( 0, -1, -t); // p6
	verts[n++] = Vec3( 0,  1, -t); // p7
	// third set
	verts[n++] = Vec3( t,  0, -1); // p8
	verts[n++] = Vec3( t,  0,  1); // p9
	verts[n++] = Vec3(-t,  0, -1); // p10
	verts[n++] = Vec3(-t,  0,  1); // p11

	// scales verts to radius and pushes them to list
	for (n = 0; n < 12; ++n)
		mVertices.push_back(Vert(glm::normalize(verts[n]), glm::normalize(verts[n])));
	
	// generates 20 triangles which make up the icosahedron
	// faces about point 0
	mFaces.push_back(Tri( 0, 11,  5));
	mFaces.push_back(Tri( 0,  5,  1));
	mFaces.push_back(Tri( 0,  1,  7));
	mFaces.push_back(Tri( 0,  7, 10));
	mFaces.push_back(Tri( 0, 10, 11));
	// adjacent faces
	mFaces.push_back(Tri( 1,  5,  9));
	mFaces.push_back(Tri( 5, 11,  4));
	mFaces.push_back(Tri(11, 10,  2));
	mFaces.push_back(Tri(10,  7,  6));
	mFaces.push_back(Tri( 7,  1,  8));
	// faces about point 3
	mFaces.push_back(Tri( 3,  9,  4));
	mFaces.push_back(Tri( 3,  4,  2));
	mFaces.push_back(Tri( 3,  2,  6));
	mFaces.push_back(Tri( 3,  6,  8));
	mFaces.push_back(Tri( 3,  8,  9));
	// adjacent faces
	mFaces.push_back(Tri( 4,  9,  5));
	mFaces.push_back(Tri( 2,  4, 11));
	mFaces.push_back(Tri( 6,  2, 10));
	mFaces.push_back(Tri( 8,  6,  7));
	mFaces.push_back(Tri( 9,  8,  1));

	// subdivides n times
	for (n = 0; n < mSubdivisions; ++n)
		subdivide();

	// scales the sphere
	for (n = 0; n < mVertices.size(); ++n)
		mVertices[n].position *= mRadius;

	// calculates face normals
	calcFaceNorms();
}

void IcoSphere::subdivide()
{
	GEint n;
	vector<Tri> subDivFaces;

	// recreate faces
	for (auto iter = mFaces.begin(); iter != mFaces.end(); iter++)
	{
		GEuint mdpta = midpoint(iter->a, iter->b);
		GEuint mdptb = midpoint(iter->b, iter->c);
		GEuint mdptc = midpoint(iter->c, iter->a);

		// adds new faces
		subDivFaces.push_back(Tri(iter->a, mdpta, mdptc));
		subDivFaces.push_back(Tri(iter->b, mdptb, mdpta));
		subDivFaces.push_back(Tri(iter->c, mdptc, mdptb));
		subDivFaces.push_back(Tri(  mdpta, mdptb, mdptc));
	}
	mFaces = subDivFaces;
}

void IcoSphere::calcFaceNorms()
{
	// clears old normals (if any)
	mFaceNormals.clear();

	GEint i;
	Tri f;
	Vec3 a, b, c;
	Tri* faces = &mFaces[0];
	Vert* verts = &mVertices[0];
	for (i = 0; i < mFaces.size(); i++)
	{
		f = faces[i];
		a = verts[f.a].normal;
		b = verts[f.b].normal;
		c = verts[f.c].normal;
		mFaceNormals.push_back(calcFaceNorm(a, b, c));
	}
}

Vec3 IcoSphere::calcFaceNorm(Vec3& a, Vec3& b, Vec3& c)
{
	Vec3 avg = a + b + c;
	return avg / 3.0f;
}

GEuint IcoSphere::midpoint(GEuint p, GEuint q)
{
	// generates key
	bool firstIsSmaller = p < q;
	GEint a = firstIsSmaller ? p : q;
	GEint b = firstIsSmaller ? q : p;
	GEulong key = ((GEulong)a << 32) + b;

	// if the midpoint has already been generated reuse it
	if (mMidPointCache.count(key))
	{
		return mMidPointCache.at(key);
	}

	// not in cache, calculate it
	Vec3 p1 = (&mVertices[0])[p].position;
	Vec3 p2 = (&mVertices[0])[q].position;
	Vec3 mid = glm::normalize((p1 + p2) / 2.0f);

	// add it to the mesh and to the cache
	GEuint i = addVert(mid);
	mMidPointCache.insert(make_pair(key, i));
	return i;
}

GEuint IcoSphere::addVert(Vec3 pos)
{
	Vert v = Vert(pos, glm::normalize(pos));
	mVertices.push_back(v);
	return mVertices.size() - 1;
}