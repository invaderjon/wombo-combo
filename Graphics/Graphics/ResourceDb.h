#pragma once

#include <string>
#include <vector>
#include "Primitives.h"
#include "ResourceIds.h" // generated file containing id defines
#include "IResource.h"

#define GE_RES_TYPE_MATERIAL 1
#define GE_RES_TYPE_TEXTURE 2 
#define GE_RES_TYPE_MESH 3
#define GE_RES_TYPE_SUBMESH 4
#define GE_RES_TYPE_AUDIO 5

namespace graphics
{
	using namespace std;

	//
	// performs as a simple hashmap which maps the ids to data
	//

	class ResourceDb
	{
	public:
		// quick typedef
		typedef struct sResEntry
		{
			// pointer to where data is stored
			IResource*		data;
			// data type [useful for type confirmation]
			GEuint			type;
			// resource path (R.blah.blah) <needs to be converted to local system path>
			string			rpath;

			// resources default to unloaded
			sResEntry(string path, GEuint rtype) : data(NULL), rpath(path), type(rtype) { }
		}				ResEntry;
	private:

		// TODO: implement hashmap
		// for now will use direct indicing since it's simpler and doesn't require a hashmap implementation
		vector<sResEntry> mEntries;

		// generates entries TODO: generate table from db.xml file 
		void initialize();
	public:
		ResourceDb();
		~ResourceDb();

		// gets the resource at the specified location [but prevent editing the item]
		const ResEntry& getResource(Res res) const;

		// updates the data and state of a resource
		void updateResource(Res res, IResource* data);
	};
}