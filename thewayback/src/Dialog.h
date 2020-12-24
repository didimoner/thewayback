#pragma once
#include "Text.h"
#include "UIElement.h"

class Player;

class Dialog : public UIElement {

private:
    Text m_text;
    std::string m_fontId;
    uint16_t m_fontSize = 0;
    std::shared_ptr<Player> m_pPlayer;

public:
    Dialog(const std::string& npcId, std::shared_ptr<Player> pPlayer);

    void update() override;
    void draw() override;
    void clean() override;

private:
    void createText();
    void playVoice();
 
};