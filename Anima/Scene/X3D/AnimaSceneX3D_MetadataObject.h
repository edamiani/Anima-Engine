#ifndef __AE_SCENE_X3D__METADATA_OBJECT__
#define __AE_SCENE_X3D__METADATA_OBJECT__

#include <string>

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _MetadataObject
			{
			public:
				_MetadataObject() {}
				virtual ~_MetadataObject() {}

				std::string& getName() { return mName; }
				std::string& getStandard() { return mReference; }
				void setName(const std::string &name) { mName = name; }
				void setStandard(const std::string &standard) { mReference = standard; }

			protected:
				std::string	mName;
				std::string	mReference;
			};
		}
	}
}

#endif