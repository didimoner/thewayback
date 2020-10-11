#pragma once
#include <SDL_mixer.h>

class Log;

class SoundManager {

private:
    SoundManager() = default;

    static std::unique_ptr<SoundManager> s_pInstance;
    static Log Logger;

    std::unordered_map<std::string, Mix_Chunk*> m_sounds;
    std::unordered_map<std::string, Mix_Music*> m_music;

public:
    ~SoundManager();
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    static SoundManager& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new SoundManager());
        }

        return *s_pInstance;
    }

    // ---------------------

    bool loadMusic(const std::string& filename, const std::string& id);
    bool loadSound(const std::string& filename, const std::string& id);
    Mix_Music* getMusic(const std::string& id);
    Mix_Chunk* getSound(const std::string& id);

};