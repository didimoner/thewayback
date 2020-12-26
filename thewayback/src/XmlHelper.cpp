#include "pch.h"
#include "XmlHelper.h"
#include "Log.h"

using namespace tinyxml2;

Log XmlHelper::Logger(typeid(XmlHelper).name());

std::string XmlHelper::getStringProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropertyElement = getCustomProperty(pElementRoot, name);
    if (pPropertyElement != nullptr) {
        return pPropertyElement->Attribute("value");
    }

    Logger.warn("There is no string property of name " + name);
    return "";
}

int32_t XmlHelper::getIntProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropertyElement = getCustomProperty(pElementRoot, name);
    if (pPropertyElement != nullptr) {
        return pPropertyElement->IntAttribute("value");
    }

    Logger.warn("There is no int32_t property of name " + name);
    return 0;
}

uint32_t XmlHelper::getUnsignedProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropertyElement = getCustomProperty(pElementRoot, name);
    if (pPropertyElement != nullptr) {
        return pPropertyElement->UnsignedAttribute("value");
    }

    Logger.warn("There is no int32_t property of name " + name);
    return 0;
}

float_t XmlHelper::getFloatProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropertyElement = getCustomProperty(pElementRoot, name);
    if (pPropertyElement != nullptr) {
        return pPropertyElement->FloatAttribute("value");
    }

    Logger.warn("There is no float_t property of name " + name);
    return 0;
}

bool XmlHelper::getBoolProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropertyElement = getCustomProperty(pElementRoot, name);
    if (pPropertyElement != nullptr) {
        return pPropertyElement->BoolAttribute("value");
    }

    Logger.warn("There is no bool property of name " + name);
    return false;
}

XMLElement* XmlHelper::getCustomProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropsElement = pElementRoot->FirstChildElement("properties");
    for (XMLElement* p = pPropsElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
        if (p->Attribute("name") == name) {
            return p;
        }
    }
    return nullptr;
}
