#ifndef __AE_XML_DOCUMENT__
#define __AE_XML_DOCUMENT__

#include "AnimaTypes.h"

namespace AE
{
	namespace Xml
	{
		class Element;

		class Document
		{
		public:
											Document() {  }
			virtual 						~Document() {  }

			virtual AE::Xml::Element* 		getRootElement() = 0;
		};
	}
}

#endif
