#pragma once
#include "Drawable.h"

class Player;
class Npc;
class UIElement;

class UserInterface : public Drawable {

private:
    std::vector<std::shared_ptr<UIElement>> m_uiElements;
    std::shared_ptr<Player> m_pPlayer;

public:
    UserInterface(std::shared_ptr<Player> pPlayer);

    void startDialog(const std::string& npcId);

    void update() override;
    void draw() override;

};