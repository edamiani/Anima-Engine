#include "../include/AnimaXmlDocumentFactory.h"

#include "../include/AnimaXmlDocumentFactoryRapidXml.h"

AE::Xml::DocumentFactory* AE::Xml::DocumentFactory::mInstance = 0;

namespace AE
{
	namespace Xml
	{
		DocumentFactory::DocumentFactory()
		{
		}

		DocumentFactory::~DocumentFactory()
		{
		}

		AE::Xml::DocumentFactory* DocumentFactory::initialize(AE::Xml::DocumentFactoryType documentFactoryType)
		{
			if(!mInstance)
			{
				switch(documentFactoryType)
				{
				case AE::Xml::DFT_RAPID_XML:
					mInstance = new AE::Xml::DocumentFactoryRapidXml();
					break;
				}
			}

			return mInstance;
		}

		void DocumentFactory::shutdown()
		{
			if(mInstance)
			{
				delete mInstance;
				mInstance = 0;
			}
		}
	}
}