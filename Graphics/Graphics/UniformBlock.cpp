#include "UniformBlock.h"

using namespace graphics;

UniformBlock::UniformBlock(GEint program, const string& name, GEint index)
	: IIdentifiable(), mProgram(program), mName(name), mIndex(index)
{
}


UniformBlock::~UniformBlock()
{
}

ID UniformBlock::id() const
{
	return mId;
}

void UniformBlock::bind(ID id)
{
	mId = id;
}

const string& UniformBlock::name() const
{
	return mName;
}

GEint UniformBlock::program() const
{
	return mProgram;
}

GEuint UniformBlock::buffer() const
{
	return mBuffer;
}

GEint UniformBlock::size() const
{
	return mSize;
}

GEuint UniformBlock::binding() const
{
	return mBinding;
}

GEint UniformBlock::index() const
{
	return mIndex;
}

void UniformBlock::push(GEint offset, GEuint size, void* data) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, mBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBlock::bind()
{
	// gets the size
	glGetActiveUniformBlockiv(mProgram, mIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &mSize);
	
	// binding is always defaulted to the id to ensure it's always unique
	// TODO: check if shared, if so utilize shared buffer and binding
	mBinding = id();

	// binds to the unique binding
	glUniformBlockBinding(mProgram, mIndex, mBinding);

	// generates, binds, and fills buffer
	glGenBuffers(1, &mBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, mBuffer);
	glBufferData(GL_UNIFORM_BUFFER, mSize, NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, mBinding, mBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// gets offsets at run time due to lack of introspective methods to 
	// obtain variable names
}