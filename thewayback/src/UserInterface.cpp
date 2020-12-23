#include "pch.h"
#include "UserInterface.h"
#include "GameObject.h"
#include "UIElement.h"
#include "Dialog.h"


UserInterface::UserInterface(std::shared_ptr<Player> pPlayer) {
    m_pPlayer = std::move(pPlayer);
}

void UserInterface::startDialog(const std::string& npcId) {
    m_uiElements.push_back(std::make_shared<Dialog>(npcId, m_pPlayer));
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
