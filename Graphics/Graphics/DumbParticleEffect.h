#pragma once
#include <vector>
#include <random>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Graphics.h"
#include "IRenderable.h"
#include "Program.h"

using namespace std;

namespace graphics
{

	class DumbParticleEffect
		: IRenderable
	{
	private:
		// dumb nested structs

		typedef struct	sParticle
		{
			Vec3		initPos;
			Vec3		initVel;
			Vec3		acc;
			GEfloat		age;
			GEfloat		TTL;
		}				Particle;

		// dumb private variables

		vector<Particle> mParticles;
		GEint mMaxParticles;
	public:
		DumbParticleEffect(GEint maxParticles);
		~DumbParticleEffect();

		void push(Program* program);
		void update(Mat4* viewMatrix, GEdouble dt);
		void render(Program* program);
		void spawn();
		inline GEfloat random(GEfloat  minimum, GEfloat maximum);
	};

}