#pragma once

#include "Graphics.h"

#define MaterialBinding 2

namespace graphics
{
	typedef struct sAttributes
	{
		GEuint position;
		GEuint normal;

		sAttributes() : position(0), normal(0) { }
		sAttributes(GEuint pos, GEuint norm) : position(pos), normal(norm) { }
	}				Attributes;

	typedef struct sMatrices
	{
		Mat4 model;
		Mat4 view;
		Mat4 projection;
		Mat3 normal;
		sMatrices() : model(), view(), projection(), normal() { }
	}				Matrices;

	typedef struct sMatricesIndices
	{
		GEuint model;
		GEuint view;
		GEuint projection;
		GEuint normal;

		sMatricesIndices() : model(0), view(0), projection(0), normal(0) { }
	}			MatricesIndices;

	typedef struct sMaterial
	{
		Vec3 diffuse;
		Vec3 ambient;
		Vec3 specular;
		GEfloat shininess;

		sMaterial() : diffuse(), ambient(), specular(), shininess(0.0f) { }
	}				Material;

	typedef struct sUniformBlock
	{
		GEuint binding;
		GEuint buffer;

		sUniformBlock() : binding(MaterialBinding), buffer(0) { }
	}				UniformBlock;

	typedef struct sShaderIndices
	{
		Attributes attrs;
		MatricesIndices matrices;
		UniformBlock material;
	}				ShaderIndices;
}