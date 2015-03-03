#include "Node.h"

using namespace graphics;

GEuint Node::sCurId = -1;

Node::Node() : mId(nextId())
{
}


Node::~Node()
{
}

GEuint Node::id() const
{
	return mId;
}

GEuint Node::nextId()
{
	return ++sCurId;
}