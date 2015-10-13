#ifndef __AE_XML_DOCUMENT_FACTORY_RAPID_XML__
#define __AE_XML_DOCUMENT_FACTORY_RAPID_XML__

#include "AnimaXmlDocumentFactory.h"
#include "rapidxml.hpp"

#include <map>

namespace AE
{
	namespace Xml
	{
		class DocumentFactoryRapidXml : public AE::Xml::DocumentFactory
		{
		public:
								DocumentFactoryRapidXml() {  }
								~DocumentFactoryRapidXml();

			AE::Xml::Document* 	createDocument(const std::string &fileName);
			void 				destroyDocument(AE::Xml::Document *document);
		};
	}
}

#endif
