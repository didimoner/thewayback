#include "pch.h"
#include "XmlHelper.h"
#include "Log.h"
#include "Animation.h"
#include "Player.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"

using namespace tinyxml2;

Log XmlHelper::Logger(typeid(XmlHelper).name());

std::shared_ptr<GameObject> XmlHelper::parseGameObject(tinyxml2::XMLElement* pObjectElement) {
    const std::string gameObjectType = pObjectElement->Attribute("type");
    std::shared_ptr<GameObject> pGameObject = GameObjectFactory::instance().create(gameObjectType);

    GameObject::InitParams gameObjectInitParams;
    gameObjectInitParams.x = pObjectElement->FloatAttribute("x");
    gameObjectInitParams.y = pObjectElement->FloatAttribute("y");
    gameObjectInitParams.width = pObjectElement->UnsignedAttribute("width");
    gameObjectInitParams.height = pObjectElement->UnsignedAttribute("height");

    Sprite::InitParams spriteInitParams;
    spriteInitParams.gameObjectInitParams = gameObjectInitParams;
    spriteInitParams.row = pObjectElement->UnsignedAttribute("row");
    spriteInitParams.frame = pObjectElement->UnsignedAttribute("frame");
    spriteInitParams.textureId = getStringProperty(pObjectElement, "textureId");

    auto textureFile = getStringProperty(pObjectElement, "textureFile");
    TextureManager::instance().load(textureFile, spriteInitParams.textureId);

    Animation::InitParams animationInitParams;
    if (getBoolProperty(pObjectElement, "animated")) {
        animationInitParams.spriteInitParams = spriteInitParams;
        animationInitParams.speed = getUnsignedProperty(pObjectElement, "animationSpeed");
        animationInitParams.totalFrames = getUnsignedProperty(pObjectElement, "animationTotalFrames");
        animationInitParams.defaultFrame = getUnsignedProperty(pObjectElement, "animationDefaultFrame");
        animationInitParams.type = getStringProperty(pObjectElement, "animationType") == "BOUNCE"
            ? EAnimationType::BOUNCE
            : EAnimationType::NORMAL;
    }

    if (gameObjectType == "player") {
        Player::InitParams playerInitParams;
        playerInitParams.animationInitParams = animationInitParams;
        playerInitParams.walkingSpeed = getFloatProperty(pObjectElement, "walkingSpeed");
        playerInitParams.runningSpeed = getFloatProperty(pObjectElement, "runningSpeed");
        std::dynamic_pointer_cast<Player>(pGameObject)->init(playerInitParams);
    }

    return pGameObject;
}

std::string XmlHelper::getStringProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropertyElement = getCustomProperty(pElementRoot, name);
    if (pPropertyElement != nullptr) {
        return pPropertyElement->Attribute("value");
    }

    Logger.warn("There is no string property of name " + name);
    return "";
}

int XmlHelper::getIntProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropertyElement = getCustomProperty(pElementRoot, name);
    if (pPropertyElement != nullptr) {
        return pPropertyElement->IntAttribute("value");
    }

    Logger.warn("There is no int property of name " + name);
    return 0;
}

uint32_t XmlHelper::getUnsignedProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropertyElement = getCustomProperty(pElementRoot, name);
    if (pPropertyElement != nullptr) {
        return pPropertyElement->UnsignedAttribute("value");
    }

    Logger.warn("There is no int property of name " + name);
    return 0;
}

float XmlHelper::getFloatProperty(XMLElement* pElementRoot, const std::string& name) {
    XMLElement* pPropertyElement = getCustomProperty(pElementRoot, name);
    if (pPropertyElement != nullptr) {
        return pPropertyElement->FloatAttribute("value");
    }

    Logger.warn("There is no float property of name " + name);
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
