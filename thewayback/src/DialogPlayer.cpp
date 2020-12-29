#include "pch.h"
#include "DialogPlayer.h"
#include "Player.h"
#include "Npc.h"
#include "Config.h"
#include "Dialog.h"


DialogPlayer::DialogPlayer(std::shared_ptr<Npc> pNpc, std::shared_ptr<Player> pPlayer) {
    m_pPlayer = std::move(pPlayer);
    m_pPlayer->lock();
    m_pNpc = std::move(pNpc);

    m_fontId = Config::instance().get("game").Get("dialog", "fontId", "default");
    m_fontSize = static_cast<uint16_t>(Config::instance().get("game").GetInteger("dialog", "fontSize", 16));

    createText();
    playVoice();
}

void DialogPlayer::update() {
    m_text.update();

    if (!m_text.isActive()) {
        m_pPlayer->unlock();
        onComplete();
    }
}
 
void DialogPlayer::draw() {
    m_text.draw();
}

void DialogPlayer::clean() {
}

void DialogPlayer::createText() {
    // todo: move to a config or outside
    GameObject::InitParams gameObjectInitParams;
    gameObjectInitParams.x = 200;
    gameObjectInitParams.y = 32;
    gameObjectInitParams.width = 480;
    gameObjectInitParams.height = m_fontSize * 2;
    gameObjectInitParams.zIndex = 200;
    ScrollableText::InitParams textInitParams;
    textInitParams.gameObjectInitParams = gameObjectInitParams;
    textInitParams.fontId = m_fontId;
    textInitParams.color = { 255, 0, 0 };
    textInitParams.text = m_pNpc->getDialogs()[0]->getPhrases()[0].text;

    m_text.init(textInitParams);
}

void DialogPlayer::playVoice() {
}
