#include "pch.h"
#include "SoundManager.h"
#include "Log.h"
#include "SystemUtils.h"

std::unique_ptr<SoundManager> SoundManager::s_pInstance;
Log SoundManager::Logger(typeid(SoundManager).name());

SoundManager::~SoundManager() {
    for (auto const& entry : m_sounds) {
        Mix_FreeChunk(entry.second);
    }
    m_sounds.clear();

    for (auto const& entry : m_music) {
        Mix_FreeMusic(entry.second);
    }
    m_music.clear();
}

bool SoundManager::loadMusic(const std::string& filename, const std::string& id) {
    if (m_music.find(id) != m_music.end()) {
        return true;
    }

    Logger.debug("Loading music: " + filename);

    const std::string resourcesPath = getResourcePath("music");
    const std::string filepath = resourcesPath + filename;
    Mix_Music* pMusic = Mix_LoadMUS(filepath.c_str());
    if (pMusic == nullptr) {
        Logger.error("Cannot load music from file: " + filepath);
        return false;
    }

    m_music[id] = pMusic;
    return true;
}

bool SoundManager::loadSound(const std::string& filename, const std::string& id) {
    if (m_sounds.find(id) != m_sounds.end()) {
        return true;
    }

    Logger.debug("Loading sound: " + filename);

    const std::string resourcesPath = getResourcePath("sounds");
    const std::string filepath = resourcesPath + filename;
    Mix_Chunk* pChunk = Mix_LoadWAV(filepath.c_str());
    if (pChunk == nullptr) {
        Logger.error("Cannot load sound from file: " + filepath);
        return false;
    }

    m_sounds[id] = pChunk;
    return true;
}

Mix_Music* SoundManager::getMusic(const std::string& id) {
    return m_music[id];
}

Mix_Chunk* SoundManager::getSound(const std::string& id) {
    return m_sounds[id];
}
