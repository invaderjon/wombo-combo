#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <vector>
#include <string>
#include <cimg/CImg.h>
#include <iostream>
#include "Graphics.h"
#include "IRenderable.h"
#include "Buffers.h"

using namespace std; 
using namespace cimg_library;

namespace graphics
{
	class HeightMap :
		public IRenderable
	{
	public:
		HeightMap(GEfloat maxHeight = 1.0f);
		HeightMap(string path, GEfloat maxHeight = 1.0f);
		~HeightMap();
		virtual void push(Attributes& attr);
		virtual void update(Mat4* viewMatrix);
		virtual void render(ShaderIndices* indices);
	private:
		// loads and processes the heightmap image using a given string path
		void loadImage(string path);

		// decodes the image into an array of values from 0 to 1
		vector<GEfloat> decodeImage(string path, GEuint& width, GEuint& height);

		// calculates a set of vertices using image dimensions and an array of color values (0 to 1)
		void genVertices(vector<Vert>& out, GEfloat* zCoords, GEuint width, GEuint height);

		// calculates the traingular mesh from the vertices
		void calcMesh(vector<Tri>& out, Vert* vertices, GEuint width, GEuint height);

		// calculates the face normals
		void calcFaceNormals(vector<Vec3>& normals, Tri* triangles, Vert* vertices, GEuint count);

		// calculates the vertex normals and stores it in the vertices
		void  calcVertexNormals(vector<Tri>& triangles, vector<Vec3>& faceNormals, vector<Vert>& vertices);

		// calculates a face normal using the verts presented as vecs
		inline Vec3 calcFaceNormal(Vec3& a, Vec3& b, Vec3& c);

		// clears all the data
		void clear();

		// instance variables
		GEfloat mMaxHeight;
		vector<Vert> mVertices;
		vector<Tri>  mFaces;
		vector<Vec3> mFaceNormals;
	};
}