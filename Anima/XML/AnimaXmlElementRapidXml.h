#ifndef __AE_XML_ELEMENT_RAPID_XML__
#define __AE_XML_ELEMENT_RAPID_XML__

#include "AnimaXmlElement.h"
#include "rapidxml.hpp"

#include <list>

namespace AE
{
	namespace Xml
	{
		class ElementRapidXml : public AE::Xml::Element
		{
		public:
										ElementRapidXml(rapidxml::xml_node<> *element, AE::Xml::Element *parent = 0) : mElement(element), mParentElement(parent), mNextSibling(0) {  }
			virtual						~ElementRapidXml();

			void						addChild(AE::Xml::Element* child) { mChildren.push_back(child); }
			std::string					getAttributeValue(const std::string &attribute);
			AE::Xml::Element*			getFirstChildByName(const std::string &name);
			AE::Xml::Element*			getFirstChild() { if(!mChildren.empty()) {mChildrenIterator = mChildren.begin(); return mChildren.front();} else return 0; }
			AE::Xml::Element*			getLastChild() { if(!mChildren.empty()) return mChildren.back(); else return 0; }
			std::string					getName() { return std::string(mElement->name()); }
			AE::Xml::Element*			getNextChild() { if(++mChildrenIterator != mChildren.end()) return *mChildrenIterator; return 0; }
			AE::Xml::Element*			getNextSibling() { return mNextSibling; }
			AE::Xml::Element*			getParent() { return mParentElement; }
			AE::Xml::Element*			getNextSiblingByName(const std::string &name);
			void 						setAttributeValue(const std::string &attribute, const std::string &value);
			void						setNextSibling(AE::Xml::Element* nextSibling) { mNextSibling = nextSibling; }

			rapidxml::xml_node<>*		_getRapidXmlElement() { return mElement; }
		private:
			rapidxml::xml_node<>		*mElement;
			AE::Xml::Element			*mParentElement;
			AE::Xml::Element			*mNextSibling;
			
			std::list<AE::Xml::Element*>			mChildren;
			std::list<AE::Xml::Element*>::iterator	mChildrenIterator;
		};
	}
}

#endif
