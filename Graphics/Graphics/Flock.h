#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <random>
#include <cmath>
#include <glm/gtc/matrix_inverse.hpp>
#include "Platform.h"
#include "Primitives.h"
#include "Graphics.h"
#include "IRenderable.h"
#include "Buffers.h"

#define BOID_COLISION_RADIUS 0.2f
#define BOID_MAX_VELOCITY 1.0f

namespace graphics
{

	class Flock
		: IRenderable
	{
	private:
		typedef struct sBoid
		{
			Vec3	   pos;
			Vec3	   vel;

			sBoid()
				: sBoid(Vec3(0)) { }
			sBoid(GEfloat radius)
			{
				// calculate position on initial sphere
				GEfloat x = 2*(static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				GEfloat y = 2*(static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				GEfloat z = 2*(static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				GEfloat w = M_PI * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX));
				Vec3 axis = glm::normalize(Vec3(x, y, z));
				Quat rot = glm::angleAxis(w, axis);
				pos = Vec3(0, 0, radius);
				pos = rot * pos;

				// calculates velocity (which affects direction)
				x = 2 * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				y = 2 * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				z = 2 * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				axis = glm::normalize(Vec3(x, y, z));
				vel = Vec3(0, 0, 2);//axis;
			}
			sBoid(Vec3 position) 
				: sBoid(position, Vec3(0)) {}
			sBoid(Vec3 position, Vec3 velocity)
				: pos(position), vel(velocity) { }
		}              Boid;

		// rule interface
		class IRule
		{
		public:
			virtual Vec3 apply(GEuint boid, Boid* neighbors, GEuint count) = 0;
		};
		
		// because lambda classes/methods would feel too dirty for c++
		// still feels disgustingly dirty tho
		// TODO: clean up
		class CohesionRule
			: public IRule
		{
		public:
			virtual Vec3 apply(GEuint boid, Boid* neighbors, GEuint count)
			{
				GEuint i;

				// calculates perceived center
				Vec3 c = Vec3(0);
				for (i = 0; i < count; i++)
				{
					if (i != boid)
						c += neighbors[i].pos;
				}
				c /= count - 1;

				// apply velocity change
				return (c - neighbors[boid].pos) / 1000.0f;
			}
		};

		class SeperationRule
			: public IRule
		{
		public:
			virtual Vec3 apply(GEuint boid, Boid* neighbors, GEuint count)
			{
				Vec3 v = Vec3(0);
				Boid b = Boid(neighbors[boid]);
				for (GEuint i = 0; i < count; i++)
				{
					if (i != boid && glm::length(b.pos - neighbors[i].pos) < BOID_COLISION_RADIUS)
					{
						v -= (b.pos - neighbors[i].pos)*10.0f;
					}
				}
				return v;
			}
		};

		class AlignmentRule
			: public IRule
		{
		public:
			virtual Vec3 apply(GEuint boid, Boid* neighbors, GEuint count)
			{
				Boid b = neighbors[boid];
				Vec3 v = Vec3(0);
				GEfloat minDist = numeric_limits<GEfloat>::max();
				for (GEuint i = 0; i < count; i++)
				{
					if (i != boid && glm::length(b.pos - neighbors[i].pos) < minDist)
					{
						minDist = glm::length(b.pos - neighbors[i].pos);
						v = neighbors[i].vel;
					}
				}
				
				return (v - neighbors[boid].vel) / 10.0f;
			}
		};

		class RadiusRule
			: public IRule
		{
		public:
			virtual Vec3 apply(GEuint boid, Boid* neighbors, GEuint count)
			{
				Vec3 p = neighbors[boid].pos;
				Vec3 v = neighbors[boid].vel;
				GEfloat l = glm::length(p);
				return Vec3(0);//(-p * (l / 5.0f))/10.0f;
				//return Vec3(0);
			}
		};

		// Applies all the rules to all of the boids
		void applyRules(GEdouble elapsed);
		
		// The local variables
		Boid* mBoids;
		Boid* mTemp;
		GEuint mCount;
		IRule** mRules;
		GEuint mRuleCount;
		GEuint mMBO;
		Mat4* mMatrices;
		Vert mVerts[5];
		Tri mFaces[6];
	public:
		Flock(GEuint count, GEfloat radius);
		~Flock();
		
		// IRenderable methods
		void push(Program* program);
		void update(Mat4* viewMatrix, GEdouble elapsed);
		void render(Program* program);
	};

}