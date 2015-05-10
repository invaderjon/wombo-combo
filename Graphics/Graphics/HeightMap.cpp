#include "HeightMap.h"

using namespace graphics;

HeightMap::HeightMap(GEfloat maxHeight)
	: mMaxHeight(maxHeight), mVertices(), mFaces(), mFaceNormals(), mDrawCount(0)
{
	GEfloat dif = .7;
	GEfloat amb = 0x10 / GEfloat(0xFF);
	GEfloat spec = 1.0f;
	GEfloat shin = 0.5f;

	/*mMaterial.diffuse = Vec3(.7f, .7f, .7f);
	mMaterial.ambient = Vec3(.1f, .1f, .1f);
	mMaterial.specular = Vec3(1.0f, 1.0f, 1.0f);
	mMaterial.shininess = shin;*/
}

HeightMap::HeightMap(string path, GEfloat maxHeight)
	: mMaxHeight(maxHeight), mVertices(), mFaces(), mFaceNormals(), mDrawCount(0)
{
	grass = new Texture("Resources/textures/heightmap/grass.bmp", GL_REPEAT, 0);
	dirt = new Texture("Resources/textures/heightmap/dirt.bmp", GL_REPEAT, 1);
	rock = new Texture("Resources/textures/heightmap/rock.bmp", GL_REPEAT, 2);
	snow = new Texture("Resources/textures/heightmap/snow.bmp", GL_REPEAT, 3);
	loadImage(path);
} 

HeightMap::~HeightMap()
{
}

void HeightMap::push(Program* program)
{
	// pushes to the buffer
	mVAO = Buffers::nextBuffer();
	mVBO = Buffers::nextBuffer();
	mIBO = Buffers::nextBuffer();

	// appends some extra space for duplicate triangles when culling
	for (int i = 0; i < mFaces.size() / 2; ++i)
		mFaces.push_back(Tri());

	// generates a vao
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// loads data
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vert), &mVertices[0], GL_STATIC_DRAW);

	// sets attributes
	glVertexAttribPointer(program->resource(VERT_POSITION), 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);
	glVertexAttribPointer(program->resource(VERT_NORMAL), 3, GL_FLOAT, GL_TRUE, sizeof(Vert), (void*)(3 * sizeof(GEfloat)));

	// enables attributes
	glEnableVertexAttribArray(program->resource(VERT_POSITION));
	glEnableVertexAttribArray(program->resource(VERT_NORMAL));

	// loads indices
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mFaces.size() * sizeof(Tri), &mFaces[0], GL_STATIC_DRAW);

	// unbinds VAO
	glBindVertexArray(0);
}

void HeightMap::update(Mat4* view, GEdouble elapsed)
{
	mModelMatrix = Mat4();
	mModelMatrix[0][0] = mModelMatrix[1][1] = mModelMatrix[2][2] = mModelMatrix[3][3] = 1.0f;
	Mat3 modelView = Mat3(mModelMatrix * *view);
	mNormalMatrix = glm::inverseTranspose(modelView);
}

void HeightMap::render(Program* program)
{
	// updates matrices
	glUniformMatrix4fv(program->resource(MAT_MODEL), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
	glUniformMatrix3fv(program->resource(MAT_NORMAL), 1, GL_FALSE, glm::value_ptr(mNormalMatrix));

	// sets texture uniforms
	glUniform1i(program->resource("grassTex"), grass->id());
	glUniform1i(program->resource("dirtTex"), dirt->id());
	glUniform1i(program->resource("rockTex"), rock->id());
	glUniform1i(program->resource("snowTex"), snow->id());

	// grass
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grass->handle());

	// dirt
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dirt->handle());

	// rock
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, rock->handle());

	// snow
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, snow->handle());
	
	// loads material
	/*glBindBuffer(GL_UNIFORM_BUFFER, indices->material.buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Material), &mMaterial);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);*/

	// draws height map
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, mDrawCount*3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void HeightMap::cull(Octree* octree, const Frustum& frustum)
{
	mDrawCount = octree->intersect(42, frustum, &mFaces[0]);
	
	//printf("Draw Count: %i\n", mDrawCount);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, mDrawCount * sizeof(Tri), &mFaces[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void HeightMap::loadImage(string path)
{
	// clear data
	clear();

	// creates height and width variables
	GEuint width, height;

	// decodes the image
	vector<GEfloat> vals = decodeImage(path, width, height);

	// if it failed to load stop
	if (vals.empty())
	{
		cout << "Failed to load heightmap (path: " << path << ")." << endl;
		return;
	}

	// generate vertices from floats
	genVertices(mVertices, &vals[0], width, height);

	// calculates triangle mesh for vertices
	calcMesh(mFaces, &mVertices[0], width, height);

	// calculates the face normals
	calcFaceNormals(mFaceNormals, &mFaces[0], &mVertices[0], mFaces.size());

	// calculates the vertex normals using the face normals
	calcVertexNormals(mFaces, mFaceNormals, mVertices);
}

vector<GEfloat> HeightMap::decodeImage(string path, GEuint& width, GEuint& height)
{
	// loads the image
	CImg<unsigned char> image;
	image.load(path.c_str());

	// gets dimensions
	width = image.width();
	height = image.height();

	// creates vector to hold values
	vector<GEfloat> vals;
	GEfloat v;

	// calculates the value of each pixel and stores it in the vector
	GEuint x, y;
	GEfloat mx = 0;
	GEfloat mn = 0;
	GEfloat lum;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			lum = (GEfloat(.21f)*image(x, y, 0, 0) + 
				   GEfloat(.72f)*image(x, y, 0, 1) + 
				   GEfloat(.07f)*image(x, y, 0, 2))/GEfloat(255.0f);
			v = mMaxHeight * lum;
			mx = std::fmax(mx, v);
			mn = std::fmin(mn, v);
			vals.push_back(v);
		}
	}

	cout << "Multiplier: " << mMaxHeight << "  Min: " << mn << "  Max: " << mx << endl;

	return vals;
}

void HeightMap::genVertices(vector<Vert>& out, GEfloat* zCoords, GEuint width, GEuint height)
{
	GEuint largest = width >= height ? width : height;
	GEdouble xIncr = 2 * (width / GEdouble(largest * largest));
	GEdouble yIncr = 2 * (height / GEdouble(largest * largest));
	GEuint r, c;

	cout << "Xincr: " << xIncr << "  Yinc: " << yIncr << endl;

	for (r = 0; r < height; r++)
	{
		for (c = 0; c < width; c++)
		{
			out.push_back(Vert(
				Vec3(GEfloat(xIncr * c - 1), GEfloat(yIncr * r - 1), zCoords[r * width + c]),
				Vec3()));
		}
	}
}

void HeightMap::calcMesh(vector<Tri>& out, Vert* vertices, GEuint width, GEuint height)
{
	// clears the old mesh
	out.clear();

	// creates [r, c], [r, c + 1], [r + 1, c] triangles
	// and [r, c + 1], [r + 1, c], [r + 1, c + 1] triangles
	GEuint row, col;
	GEuint a, b, c;
	GEuint t;

	for (row = 0; GEint(row) < GEint(height - 1); row++)
	{
		for (col = 0; GEint(col) < GEint(width - 1); col++)
		{
			// determines triangle vertices
			a = row * width + col;
			b = row * width + col + 1;
			c = (row + 1) * width + col;

			// ensures triangle is CCW
			if (calcFaceNormal(vertices[a].position, vertices[b].position, vertices[c].position).z < 0) {
				t = b;
				b = c;
				c = t;
			}

			// adds the triangle to the list
			out.push_back(Tri(a, b, c));

			// dtermines triangle vertices
			a = row * width + col + 1;
			b = (row + 1) * width + col;
			c = (row + 1) * width + col + 1;

			// ensures triangle is CCW
			if (calcFaceNormal(vertices[a].position, vertices[b].position, vertices[c].position).z < 0) {
				t = b;
				b = c;
				c = t;
			}

			// adds the triangle to the list
			out.push_back(Tri(a, b, c));
		}
	}
}

void HeightMap::calcFaceNormals(vector<Vec3>& norms, Tri* tris, Vert* verts, GEuint count)
{
	GEuint i;
	Tri f;
	Vec3 a, b, c;

	for (i = 0; i < count; i++)
	{
		f = tris[i];
		a = verts[f.a].position;
		b = verts[f.b].position;
		c = verts[f.c].position;
		norms.push_back(calcFaceNormal(a, b, c));
	}
}

void HeightMap::calcVertexNormals(vector<Tri>& tris, vector<Vec3>& normals, vector<Vert>& vertices)
{
	GEuint i;
	vector<GEint> counts(vertices.size());
	Vert* verts = &vertices[0];
	GEint* c = &counts[0];

	// clear counts to zero
	for (i = 0; i < vertices.size(); i++)
		c[i] = 0;

	// iterates through all faces adding up normals
	vector<Tri>::iterator iter = tris.begin();
	vector<Vec3>::iterator norms = normals.begin();
	for (; iter != tris.end() && norms != normals.end(); iter++, norms++)
	{
		// a
		verts[(*iter).a].normal += (*norms);
		c[(*iter).a]++;

		// b
		verts[(*iter).b].normal += (*norms);
		c[(*iter).b]++;

		// c
		verts[(*iter).c].normal += (*norms);
		c[(*iter).c]++;
	}

	// averages each calculated vertex norm
	for (i = 0; i < counts.size(); i++)
	{
		verts[i].normal = glm::normalize(verts[i].normal);
		if (glm::dot(verts[i].normal, verts[i].position) < GEfloat(0.0))
			verts[i].normal = verts[i].normal;
	}
}

Vec3 HeightMap::calcFaceNormal(Vec3& a, Vec3& b, Vec3& c)
{
	Vec3 u = b - a;
	Vec3 v = c - a;

	Vec3 n = glm::cross(u, v);
	n = glm::normalize(n);
	float sin_alpha = glm::length(n) / (length(u) * length(v));

	return n * sin_alpha;
}

void HeightMap::clear()
{
	mVertices.clear();
	mFaces.clear();
	mFaceNormals.clear();
}