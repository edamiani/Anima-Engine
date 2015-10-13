#include "../include/AnimaXmlDocumentFactoryRapidXml.h"

#include "../include/AnimaException.h"
#include "../include/AnimaXmlDocumentRapidXml.h"

namespace AE
{
	namespace Xml
	{
		DocumentFactoryRapidXml::~DocumentFactoryRapidXml()
		{
		}

		AE::Xml::Document* DocumentFactoryRapidXml::createDocument(const std::string &fileName)
		{
			AE::Xml::DocumentRapidXml *document = new AE::Xml::DocumentRapidXml(fileName);
			
			if(document == 0)
				throw AE::Exception(AE::ET_FILE_NOT_FOUND, "Warning: Unable to load XML document");

			return document;
		}

		void DocumentFactoryRapidXml::destroyDocument(AE::Xml::Document *document)
		{
			assert(document);
			delete document;
		}
	}
}
