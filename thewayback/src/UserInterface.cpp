#include "pch.h"
#include "UserInterface.h"
#include "GameObject.h"
#include "UIElement.h"
#include "FontManager.h"
#include "Text.h"


void UserInterface::createTextBox(std::function<void()>& callback) {
    std::string fontId = "pixel";
    int32_t fontSize = 32;
    FontManager::instance().loadFont("pixel.ttf", fontId, fontSize);

    auto pTextBox = std::make_shared<Text>(fontId);
    pTextBox->setCallback(callback);

    GameObject::InitParams initParams;
    initParams.x = 200;
    initParams.y = 32;
    initParams.width = 480;
    initParams.height = fontSize * 2;
    initParams.zIndex = 200;
    pTextBox->init(initParams);

    std::wstring wstring = L"Привет, Мир! Это мое первое сообщение в виде текста для этой игры. Надеюсь, что оно понравится вам!";
    pTextBox->setText(wstring);

    m_uiElements.push_back(pTextBox);
}

void UserInterface::update() {
    auto it = m_uiElements.begin();
    while (it != m_uiElements.end()) {
        auto* element = it->get();
        if (!element->isActive()) {
            it = m_uiElements.erase(it);
            continue;
        }
        element->update();
        ++it;
    }
}

void UserInterface::draw() {
    for (const auto& pObject : m_uiElements) {
        pObject->draw();
    }
}
