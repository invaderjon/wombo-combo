#include "Material.h"

using namespace graphics;

Material::Material()
	: IIdentifiable()
{
}


Material::~Material()
{
}


Res Material::res() const { return 0;  }
GEuint Material::state() const { return 0; }
void Material::state(GEuint state) { }