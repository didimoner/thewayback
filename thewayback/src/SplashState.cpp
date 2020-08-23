#include "pch.h"
#include "SplashState.h"
#include "Log.h"

Log* SplashState::Logger = new Log(typeid(SplashState).name());
const std::string SplashState::s_stateId = "SPLASH_STATE";

void SplashState::update() {

}

void SplashState::draw() {

}

void SplashState::onActivate() {
    Logger->debug("Splash activated");
}

bool SplashState::onDeactivate() {
    Logger->debug("Splash deactivated");
    return false;
}
