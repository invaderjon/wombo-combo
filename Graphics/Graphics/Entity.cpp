#include "Entity.h"

using namespace graphics;

Entity::Entity()
{
}

Entity::Entity(Mesh* mesh) : mMesh(mesh)
{

}

Entity::~Entity()
{
}

Mesh* Entity::mesh() const
{
	return mMesh;
}

void Entity::mesh(Mesh* mes)
{
	mMesh = (Mesh*)mes;
}

const Vec3& Entity::position() const
{
	return mPositon;
}

void Entity::position(const Vec3& pos)
{
	mPositon = pos;
}

const Vec4& Entity::scale() const
{
	return mScale;
}

void Entity::scale(const Vec4& sca)
{
	mScale = sca;
}

const Quat& Entity::rotation() const
{
	return mRotation;
}

void Entity::rotation(const Quat& rot)
{
	mRotation = rot;
}


