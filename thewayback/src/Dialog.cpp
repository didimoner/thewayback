#include "pch.h"
#include "Dialog.h"
#include "Player.h"
#include "Config.h"


Dialog::Dialog(const std::string& npcId, std::shared_ptr<Player> pPlayer) {
    m_pPlayer = std::move(pPlayer);
    m_pPlayer->lock();

    m_fontId = Config::instance().get("game").Get("dialog", "fontId", "default");
    m_fontSize = static_cast<uint16_t>(Config::instance().get("game").GetInteger("dialog", "fontSize", 16));

    createText();
    playVoice();
}

void Dialog::update() {
    m_text.update();

    if (!m_text.isActive()) {
        m_pPlayer->unlock();
        onComplete();
    }
}
 
void Dialog::draw() {
    m_text.draw();
}

void Dialog::clean() {
}

void Dialog::createText() {
    // todo: move to a config or outside
    GameObject::InitParams gameObjectInitParams;
    gameObjectInitParams.x = 200;
    gameObjectInitParams.y = 32;
    gameObjectInitParams.width = 480;
    gameObjectInitParams.height = m_fontSize * 2;
    gameObjectInitParams.zIndex = 200;
    Text::InitParams textInitParams;
    textInitParams.gameObjectInitParams = gameObjectInitParams;
    textInitParams.fontId = m_fontId;
    textInitParams.color = { 255, 0, 0 };

    m_text.init(textInitParams);

    std::wstring wstring = L"Привет, Мир! Это мое первое сообщение в виде текста для этой игры. Надеюсь, что оно понравится вам!";
    m_text.setText(wstring);
}

void Dialog::playVoice() {
}
