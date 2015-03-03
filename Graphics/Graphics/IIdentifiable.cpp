#include "IIdentifiable.h"

using namespace graphics;

ID IIdentifiable::sCurId = GE_ID_INVALID;

IIdentifiable::IIdentifiable() : mId(nextId())
{
}


IIdentifiable::~IIdentifiable()
{
}

/// <summary>
/// Retrieves the unique id of the object.
/// </summary>
/// <returns>
/// Unique id.
/// </returns>
ID IIdentifiable::id() const
{
	return mId;
}

/// <summary>
/// Generates the next available unique id.
/// </summary>
/// <returns>A unique id.</returns>
ID IIdentifiable::nextId()
{
	return ++sCurId;
}