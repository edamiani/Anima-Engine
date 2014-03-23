#ifndef __AE_XML_DOCUMENT_RAPID_XML__
#define __AE_XML_DOCUMENT_RAPID_XML__

#include "AnimaXmlDocument.h"

#include "rapidxml.hpp"

namespace AE
{
	namespace Xml
	{
		class DocumentRapidXml : public AE::Xml::Document
		{
		public:
										DocumentRapidXml();
										DocumentRapidXml(const std::string &filename);
										~DocumentRapidXml();

			AE::Xml::Element*			getRootElement() { return mRootElement; }

		private:
			void 						_parse();
			void 						_parseElement(AE::Xml::Element *element);

			rapidxml::xml_document<>	*mDocument;
			AE::Xml::Element			*mRootElement;
		};
	}
}

#endif
