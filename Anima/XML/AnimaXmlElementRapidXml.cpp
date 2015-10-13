#include "../include/AnimaXmlElementRapidXml.h"

namespace AE
{
	namespace Xml
	{
		ElementRapidXml::~ElementRapidXml()
		{
			mElement = 0;
			mNextSibling = 0;
			mParentElement = 0;

			if(!mChildren.empty())
			{
				mChildrenIterator = mChildren.begin();
				while(mChildrenIterator != mChildren.end())
				{
					delete *mChildrenIterator;
					mChildrenIterator++;
				}
			}

			mChildren.clear();
		}

		std::string ElementRapidXml::getAttributeValue(const std::string &attribute)
		{
			for (rapidxml::xml_attribute<> *attr = mElement->first_attribute(); attr; attr = attr->next_attribute())
			{
				if(attr->name() == attribute.c_str())
					return std::string(attr->value());
			}
			
			return "";
		}

		AE::Xml::Element* ElementRapidXml::getFirstChildByName(const std::string &name)
		{
			if(!mChildren.empty())
			{
				mChildrenIterator = mChildren.begin();

				while(mChildrenIterator != mChildren.end())
				{
					if((*mChildrenIterator)->getName() == name)
						return *mChildrenIterator;

					mChildrenIterator++;
				}

				return 0;
			}
			else
				return 0;
		}

		AE::Xml::Element* ElementRapidXml::getNextSiblingByName(const std::string &name)
		{
			AE::Xml::Element *next = mNextSibling;

			while(next)
			{
				if(next->getName() == name)
					return next;
				else
					next = next->getNextSibling();
			}

			return 0;
		}

		void ElementRapidXml::setAttributeValue(const std::string &attribute, const std::string &value)
		{
			rapidxml::xml_document<> *doc = mElement->document();
			char *attributeValue = doc->allocate_string(value.c_str());
			
			for (rapidxml::xml_attribute<> *attr = mElement->first_attribute(); attr; attr = attr->next_attribute())
			{
				if(attr->name() == attribute.c_str())
					attr->value(attributeValue);
			}
		}
	}
}
