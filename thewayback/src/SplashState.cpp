#include "pch.h"
#include "SplashState.h"
#include "Log.h"
#include "FontManager.h"

Log* SplashState::Logger = new Log(typeid(SplashState).name());
const std::string SplashState::s_stateId = "SPLASH_STATE";

void SplashState::update() {

}

void SplashState::draw() {
    FontManager::instance()->draw("hello_text", 25, 32, Game::instance()->getRenderer());
}

void SplashState::onActivate() {
    Logger->debug("Splash activated");

    FontManager::instance()->loadFont("segoeui.ttf", "segoeui", 58);
    FontManager::instance()->createTexture("segoeui", "hello_text", "Hello World!", { 255,255,255 }, Game::instance()->getRenderer());
}

bool SplashState::onDeactivate() {
    Logger->debug("Splash deactivated");
    return false;
}
