#pragma once

#include <string>
#include "Platform.h"
#include "Primitives.h"
#include "IIdentifiable.h"

using namespace std;

namespace graphics
{
	class UniformBlock
		: public IIdentifiable
	{
	public:
		// creates a new block
		UniformBlock(GEint program, const string& name, GEint index);
		// destroys a block
		~UniformBlock();
		// gets the block's id
		inline ID id() const;
		// binds the block
		inline void bind(ID id);
		// gets the block's name
		inline const string& name() const;
		// gets the block's program
		inline GEint program() const;
		// gets the block's buffer
		inline GEuint buffer() const;
		// gets the block's buffer's size
		inline GEint size() const;
		// gets the block's binding
		inline GEuint binding() const;
		// gets the block's index
		inline GEint index() const;
		// pushes data to the buffer
		void push(GEint offset, GEuint size, void* data) const;
	private:
		// binds the buffer
		void bind();
		// the block's id
		ID mId;
		// the block's program
		GEint mProgram;
		// the block's index
		GEint mIndex;
		// the block's buffer
		GEuint mBuffer;
		// the block's binding
		GEuint mBinding;
		// the blocks's buffer's size
		GEint mSize;
		// the block's name
		string mName;
	};
}
