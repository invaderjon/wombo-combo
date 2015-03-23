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

#define BOID_COLISION_RADIUS 0.1f
#define BOID_MAX_VELOCITY 10.0f
#define BOID_DIR_AVG 20

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
				GEfloat x = 2 * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				GEfloat y = 2 * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				GEfloat z = 2 * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				GEfloat w = M_PI * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX));
				Vec3 axis = glm::normalize(Vec3(x, y, z));
				Quat rot = glm::angleAxis(w, axis);
				w = (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX));
				pos = Vec3(0, 0, w * radius);
				pos = rot * pos;

				// calculates velocity (which affects direction)
				x = 2 * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				y = 2 * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				z = 2 * (static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX)) - 1;
				axis = glm::normalize(Vec3(x, y, z));
				vel = axis*10.0f;
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
				c /= (count - 1);

				// apply velocity change
				return (c - neighbors[boid].pos) * 2.0f;
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
						v -= (b.pos - neighbors[i].pos);
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
				GEuint curBoid;
				GEuint curClose;
				GEuint minClose;
				Boid b = neighbors[boid];
				Vec3 v = Vec3(0);
				GEfloat len;
				GEfloat diff;
				Vec3 close[BOID_DIR_AVG];
				GEfloat dists[BOID_DIR_AVG];
				for (curBoid = 0; curBoid < BOID_DIR_AVG; curBoid++)
					dists[curBoid] = numeric_limits<GEfloat>::max();

				for (curBoid = 0; curBoid < count; curBoid++)
				{
					if (curBoid != boid)
					{
						len = glm::length(b.pos - neighbors[curBoid].pos);

						for (curClose = 0, diff = 0, minClose = -1; curClose < BOID_DIR_AVG; curClose++)
						{
							if (len < dists[curClose] && dists[curClose] - len > diff)
							{
								diff = dists[curClose] - len;
								minClose = curClose;
							}
						}
						if (minClose != -1)
						{
							dists[minClose] = glm::length(b.pos - neighbors[curBoid].pos);
							close[minClose] = neighbors[curBoid].vel;
						}
						//minDist = glm::length(b.pos - neighbors[i].pos);
						//v = neighbors[i].vel;
					}
					//if (i != boid)
					//	v += neighbors[i].vel;
				}

				for (curClose = 0; curClose < BOID_DIR_AVG; curClose++)
					v += close[curClose];

				v /= BOID_DIR_AVG;

				return (neighbors[boid].vel - v);
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
				return (p * (l / 20.0f))*4.0f;
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