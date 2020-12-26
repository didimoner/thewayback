#include "pch.h"
#include "GameObjectParser.h"
#include "Animation.h"
#include "GameObjectFactory.h"
#include "Npc.h"
#include "Player.h"
#include "TextureManager.h"
#include "XmlHelper.h"

std::shared_ptr<GameObject> GameObjectParser::parse(tinyxml2::XMLElement* pObjectElement) {
    const std::string gameObjectType = pObjectElement->Attribute("type");
    std::shared_ptr<GameObject> pGameObject = GameObjectFactory::instance().create(gameObjectType);

    GameObject::InitParams gameObjectInitParams;
    gameObjectInitParams.x = pObjectElement->FloatAttribute("x");
    gameObjectInitParams.y = pObjectElement->FloatAttribute("y");
    gameObjectInitParams.width = pObjectElement->UnsignedAttribute("width");
    gameObjectInitParams.height = pObjectElement->UnsignedAttribute("height");
    gameObjectInitParams.zIndex = XmlHelper::getIntProperty(pObjectElement, "zIndex");

    Sprite::InitParams spriteInitParams;
    spriteInitParams.gameObjectInitParams = gameObjectInitParams;
    spriteInitParams.row = XmlHelper::getUnsignedProperty(pObjectElement, "row");
    spriteInitParams.frame = XmlHelper::getUnsignedProperty(pObjectElement, "frame");
    spriteInitParams.textureId = XmlHelper::getStringProperty(pObjectElement, "textureId");

    auto textureFile = XmlHelper::getStringProperty(pObjectElement, "textureFile");
    TextureManager::instance().load(textureFile, spriteInitParams.textureId);

    Animation::InitParams animationInitParams;
    if (XmlHelper::getBoolProperty(pObjectElement, "animated")) {
        animationInitParams.spriteInitParams = spriteInitParams;
        animationInitParams.speed = XmlHelper::getUnsignedProperty(pObjectElement, "animationSpeed");
        animationInitParams.totalFrames = XmlHelper::getUnsignedProperty(pObjectElement, "animationTotalFrames");
        animationInitParams.defaultFrame = XmlHelper::getUnsignedProperty(pObjectElement, "animationDefaultFrame");
        animationInitParams.type = XmlHelper::getStringProperty(pObjectElement, "animationType") == "BOUNCE"
            ? EAnimationType::BOUNCE
            : EAnimationType::NORMAL;
    }

    if (gameObjectType == "player") {
        Player::InitParams playerInitParams;
        playerInitParams.animationInitParams = animationInitParams;
        playerInitParams.walkingSpeed = XmlHelper::getFloatProperty(pObjectElement, "walkingSpeed");
        playerInitParams.runningSpeed = XmlHelper::getFloatProperty(pObjectElement, "runningSpeed");
        std::dynamic_pointer_cast<Player>(pGameObject)->init(playerInitParams);
    } else if (gameObjectType == "npc") {
        Npc::InitParams npcInitParams;
        npcInitParams.spriteInitParams = spriteInitParams;
        std::dynamic_pointer_cast<Npc>(pGameObject)->init(npcInitParams);
    }

    return pGameObject;
}
