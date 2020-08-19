#include "pch.h"
#include "PlayState.h"

Log* PlayState::Logger = new Log(typeid(PlayState).name());
const std::string PlayState::s_stateId = "PLAY_STATE";

void PlayState::update() {
}

void PlayState::draw() {
}

void PlayState::onActivate() {
    Logger->debug("Play activated");
}

bool PlayState::onDeactivate() {
    Logger->debug("Play deactivated");
    return false;
}
