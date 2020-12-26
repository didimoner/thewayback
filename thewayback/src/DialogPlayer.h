#pragma once
#include "Text.h"
#include "UIElement.h"

class Player;
class Npc;

class DialogPlayer : public UIElement {

private:
    Text m_text;
    std::string m_fontId;
    uint16_t m_fontSize = 0;
    std::shared_ptr<Player> m_pPlayer;
    std::shared_ptr<Npc> m_pNpc;

public:
    DialogPlayer(std::shared_ptr<Npc>, std::shared_ptr<Player> pPlayer);

    void update() override;
    void draw() override;
    void clean() override;

private:
    void createText();
    void playVoice();
 
};