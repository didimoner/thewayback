#include "pch.h"
#include "FontManager.h"
#include "Log.h"
#include "SystemUtils.h"
#include "Game.h"

std::unique_ptr<FontManager> FontManager::s_pInstance;
Log FontManager::Logger(typeid(FontManager).name());

FontManager::FontManager() {
    if (TTF_Init() != 0) {
        Logger.error("SDL_ttf initialization error: " + std::string(TTF_GetError()));
    }
}

FontManager::~FontManager() {
    for (auto const& entry : m_fonts) {
        SDL_free(entry.second);
    }
    m_fonts.clear();

    for (auto const& entry : m_textures) {
        SDL_DestroyTexture(entry.second);
    }

    m_textures.clear();
}

bool FontManager::loadFont(const std::string& filename, const std::string& id, int32_t size) {
    if (m_fonts.find(id) != m_fonts.end()) {
        return true;
    }

    Logger.debug("Loading font " + filename + " of size " + std::to_string(size));

    const std::string resourcesPath = getResourcePath("fonts");
    const std::string filepath = resourcesPath + filename;
    TTF_Font* pFont = TTF_OpenFont(filepath.c_str(), size);

    if (pFont == nullptr) {
        Logger.error("Cannot load surface from image: " + filepath);
        return false;
    }

    m_fonts[id] = pFont;
    return true;
}

TTF_Font* FontManager::getFont(const std::string& fontId) {
    if (m_fonts.find(fontId) == m_fonts.end()) {
        Logger.warn("Font not found in the map: " + fontId);
        return nullptr;
    }

    return m_fonts[fontId];
}