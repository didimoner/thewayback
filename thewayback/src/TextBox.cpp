#include "pch.h"
#include "TextBox.h"
#include <SDL_ttf.h>
#include "Game.h"
#include "FontManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Log.h"
#include <chrono>
#include <thread>

TextBox::TextBox(std::string& fontId) {
    m_fontId = std::move(fontId);
}

void TextBox::update() {
    if (InputHandler::instance().isKeyPressed(SDL_SCANCODE_SPACE)) {
        int textureHeight;
        SDL_QueryTexture(m_pTexture, nullptr, nullptr, nullptr, &textureHeight);
        m_row = ++m_row % static_cast<int32_t>(std::ceil(static_cast<float_t>(textureHeight) / m_height));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void TextBox::draw() {
    int textureWidth;
    int textureHeight;
    SDL_QueryTexture(m_pTexture, nullptr, nullptr, &textureWidth, &textureHeight);

    const int32_t rowHeight = textureHeight - m_row * m_height < m_height
        ? textureHeight - m_row * m_height
        : m_height;

    SDL_Rect sourceRect;
    sourceRect.x = 0;
    sourceRect.y = static_cast<int>(m_height * m_row);
    sourceRect.w = textureWidth;
    sourceRect.h = rowHeight;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(m_position.getX());
    destRect.y = static_cast<int>(m_position.getY());
    destRect.w = m_width;
    destRect.h = rowHeight;

    Renderer::instance().send(m_pTexture, sourceRect, destRect, m_zIndex);
}

void TextBox::clean() {
}

void TextBox::setText(std::wstring& text) {
    m_text = std::move(text);
    reloadTexture();
}

void TextBox::reloadTexture() {
    if (m_pTexture != nullptr) {
        SDL_DestroyTexture(m_pTexture);
        m_pTexture = nullptr;
    }

    TTF_Font* pFont = FontManager::instance().getFont(m_fontId);
    if (pFont == nullptr) {
        return;
    }

    SDL_Surface* pSurface = TTF_RenderUNICODE_Blended_Wrapped(pFont, reinterpret_cast<const Uint16*>(m_text.c_str()), m_color, m_width);
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::instance().getRenderer(), pSurface);
    SDL_FreeSurface(pSurface);

    m_pTexture = pTexture;
}
