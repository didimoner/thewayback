#include "pch.h"
#include "SoundPlayer.h"
#include <SDL_mixer.h>
#include "SoundManager.h"

void SoundPlayer::playMusic(const std::string& musicId, int32_t loops) {
    auto* pMusic = SoundManager::instance().getMusic(musicId);
    Mix_PlayMusic(pMusic, loops);
}

void SoundPlayer::playSound(const std::string& soundId, int32_t channel, int32_t loops) {
    auto* pSound = SoundManager::instance().getSound(soundId);
    Mix_PlayChannel(channel, pSound, loops);
}
