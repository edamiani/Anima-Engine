#include "../include/AnimaXmlDocumentRapidXml.h"
#include "../include/AnimaXmlElementRapidXml.h"

#include <fstream>
#include <sstream>

namespace AE
{
	namespace Xml
	{
		DocumentRapidXml::DocumentRapidXml()
		{
			mDocument = new rapidxml::xml_document<>();
			assert(mDocument != 0);
		}

		DocumentRapidXml::DocumentRapidXml(const std::string &filename)
		{
			mDocument = new rapidxml::xml_document<>();
			assert(mDocument != 0);

			std::ifstream documentStream(filename.c_str());
			std::ostringstream out;

			out << documentStream.rdbuf();

			std::string text = out.str();
			char *name = const_cast<char *>(text.c_str());
			mDocument->parse<0>(name);
			_parse();
		}

		DocumentRapidXml::~DocumentRapidXml()
		{
			if(mDocument)
			{
				delete mDocument;
				mDocument = 0;
			}

			if(mRootElement)
			{
				delete mRootElement;
				mRootElement = 0;
			}
		}

		void DocumentRapidXml::_parse()
		{
			mRootElement = new AE::Xml::ElementRapidXml(mDocument->first_node());
			assert(mRootElement != 0);
			_parseElement(mRootElement);
		}

		void DocumentRapidXml::_parseElement(AE::Xml::Element *element)
		{
			rapidxml::xml_node<> *child = 0;
			child = static_cast<AE::Xml::ElementRapidXml *>(element)->_getRapidXmlElement()->first_node();

			AE::Xml::ElementRapidXml *currentElement = 0;
			AE::Xml::ElementRapidXml *previousElement = 0;

			while(child)
			{
				if(currentElement)
					previousElement = currentElement;

				currentElement = new AE::Xml::ElementRapidXml(child, element);

				if(previousElement)
					previousElement->setNextSibling(currentElement);

				element->addChild(currentElement);
				if(child->first_node())
					_parseElement(element->getLastChild());

				child = child->next_sibling();
			}
		}
	}
}
