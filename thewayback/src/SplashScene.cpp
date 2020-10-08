#include "pch.h"
#include "SplashScene.h"
#include "Log.h"
#include "FontManager.h"
#include "Game.h"

Log SplashScene::Logger(typeid(SplashScene).name());
const std::string SplashScene::SCENE_ID = "SPLASH_SCENE";

void SplashScene::update() {

}

void SplashScene::draw() {
    FontManager::instance().draw("hello_text", 25, 32);
}

void SplashScene::onActivate() {
    Logger.debug("Splash activated");

    FontManager::instance().loadFont("segoeui.ttf", "segoeui", 16);
    FontManager::instance().createMultilineTexture("segoeui", "hello_text", 
        "Hello my dear friend!\nHow are you doing?", 320, {255, 255, 255});
}

bool SplashScene::onDeactivate() {
    Logger.debug("Splash deactivated");
    return false;
}

std::string SplashScene::getSceneId() const {
    return SCENE_ID;
}
