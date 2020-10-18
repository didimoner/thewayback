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
}

void SplashScene::onActivate() {
    Logger.debug("Splash activated");
}

bool SplashScene::onDeactivate() {
    Logger.debug("Splash deactivated");
    return false;
}

std::string SplashScene::getSceneId() const {
    return SCENE_ID;
}
