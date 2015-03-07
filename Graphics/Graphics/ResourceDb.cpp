#include "ResourceDb.h"

using namespace graphics;

ResourceDb::ResourceDb()
	: mEntries()
{
	initialize();
}


ResourceDb::~ResourceDb()
{
}

void ResourceDb::initialize()
{
	// TODO: generate from db.xml
	mEntries.push_back(ResEntry("R.textures.heightmap.grass", GE_RES_TYPE_TEXTURE));
	mEntries.push_back(ResEntry("R.textures.heightmap.dirt", GE_RES_TYPE_TEXTURE));
	mEntries.push_back(ResEntry("R.textures.heightmap.rock", GE_RES_TYPE_TEXTURE));
	mEntries.push_back(ResEntry("R.textures.heightmap.snow", GE_RES_TYPE_TEXTURE));
	mEntries.push_back(ResEntry("R.textures.heightmap.map", GE_RES_TYPE_TEXTURE));
	mEntries.push_back(ResEntry("R.materials.terrain.heightmap", GE_RES_TYPE_MATERIAL));
}

const ResourceDb::ResEntry& ResourceDb::getResource(Res res) const
{
	// TODO: implement hashmap
	// SUPER UNSAFE AT THE MOMENT
	return (&mEntries[0])[res];
}

void ResourceDb::updateResource(Res res, IResource* data)
{
	// TODO: implement hashmap
	// SUPER UNSAFE AT THE MOMENT
	(&mEntries[0])[res].data = data;
}