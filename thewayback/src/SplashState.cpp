#include "pch.h"
#include "SplashState.h"
#include "Log.h"
#include "FontManager.h"
#include "Game.h"

Log SplashState::Logger(typeid(SplashState).name());
const std::string SplashState::s_stateId = "SPLASH_STATE";

void SplashState::update() {

}

void SplashState::draw() {
    FontManager::instance().draw("hello_text", 25, 32, Game::instance().getRenderer());
}

void SplashState::onActivate() {
    Logger.debug("Splash activated");

    FontManager::instance().loadFont("segoeui.ttf", "segoeui", 16);
    FontManager::instance().createMultilineTexture("segoeui", "hello_text", "Hello my dear friend!\nHow are you doing?", 320,
                                                   {255, 255, 255}, Game::instance().getRenderer());
}

bool SplashState::onDeactivate() {
    Logger.debug("Splash deactivated");
    return false;
}

std::string SplashState::getStateId() const {
    return s_stateId;
}
