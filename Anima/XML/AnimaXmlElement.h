#ifndef __AE_XML_ELEMENT__
#define __AE_XML_ELEMENT__

#include "AnimaTypes.h"

namespace AE
{
	namespace Xml
	{
		class Element
		{
		public:
											Element() {  }
			virtual							~Element() {  }

			virtual void					addChild(AE::Xml::Element* child) = 0;
			virtual std::string				getAttributeValue(const std::string &attribute) = 0;
			virtual AE::Xml::Element*		getFirstChildByName(const std::string &name) = 0;
			virtual AE::Xml::Element*		getFirstChild() = 0;
			virtual AE::Xml::Element*		getLastChild() = 0;
			virtual std::string				getName() = 0;
			virtual AE::Xml::Element*		getNextChild() = 0;
			virtual AE::Xml::Element*		getNextSibling() = 0;
			virtual AE::Xml::Element*		getParent() = 0;
			virtual AE::Xml::Element*		getNextSiblingByName(const std::string &name) = 0;
			virtual void 					setAttributeValue(const std::string &attribute, const std::string &value) = 0;
			virtual void					setNextSibling(AE::Xml::Element* nextSibling) = 0;
		};
	}
}

#endif
