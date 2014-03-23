#ifndef __AE_XML_DOCUMENT_FACTORY__
#define __AE_XML_DOCUMENT_FACTORY__

#include "AnimaTypes.h"

namespace AE
{
	namespace Xml
	{
		class Document;

		enum DocumentFactoryType
		{
			DFT_RAPID_XML
		};

		class DocumentFactory
		{
		public:
			virtual ~DocumentFactory();

			static AE::Xml::DocumentFactory*	getInstance() { assert(mInstance); return mInstance; }
			static AE::Xml::DocumentFactory*	initialize(AE::Xml::DocumentFactoryType documentFactoryType);
			static void shutdown();

			virtual AE::Xml::Document*	createDocument(const std::string &fileName) = 0;
			virtual void 				destroyDocument(AE::Xml::Document *document) = 0;

		protected:
			DocumentFactory();

			static AE::Xml::DocumentFactory *mInstance;
		};
	}
}

#endif
