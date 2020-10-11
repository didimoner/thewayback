#pragma once

class SoundPlayer {

public:
    static void playMusic(const std::string& musicId, int32_t loops = 0);
    static void playSound(const std::string& soundId, int32_t channel = -1, int32_t loops = 0);

};