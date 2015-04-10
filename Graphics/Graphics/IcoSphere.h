#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <unordered_map>
#include <vector>
#include "ISphere.h"

using namespace std;

namespace graphics
{
	class IcoSphere :
		public ISphere
	{
	public:
		IcoSphere(GEfloat radius, GEint subdivisions);
		~IcoSphere();

		void push(Program* program);
		void update(Mat4* view, GEdouble elapsed);
		void render(Program* program);

		GEfloat radius() const;
		GEint subdivisions() const;

	private:
		void initialize();
		void subdivide();
		void calcFaceNorms();
		Vec3 calcFaceNorm(Vec3& a, Vec3& b, Vec3& c);
		GEuint midpoint(GEuint p, GEuint q);
		GEuint addVert(Vec3 pos);

		// instance variables
		GEfloat mRadius;
		GEint mSubdivisions;
		unordered_map<GEulong, GEuint> mMidPointCache;
		vector<Vert> mVertices;
		vector<Tri> mFaces;
		vector<Vec3> mFaceNormals;
	};
}

