#ifndef __AE_SCENE_X3D__URL_OBJECT__
#define __AE_SCENE_X3D__URL_OBJECT__

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _UrlObject
			{
			public:
				_UrlObject() {}
				virtual ~_UrlObject() {}

				std::string& getUrl() { return mUrl; }
				void setUrl (const std::string& url) { mUrl = url; }

			protected:
				std::string	mUrl;
			};
		}
	}
}

#endif