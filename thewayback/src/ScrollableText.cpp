#include "pch.h"
#include "ScrollableText.h"
#include <SDL_ttf.h>
#include "Game.h"
#include "FontManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Log.h"
#include <chrono>
#include <thread>


void ScrollableText::init(const InitParams& initParams) {
    GameObject::init(initParams.gameObjectInitParams);
    m_pFont = FontManager::instance().getFont(initParams.fontId);
    m_color = initParams.color;
    m_text = initParams.text;

    loadTexture();
}

void ScrollableText::update() {
    if (InputHandler::instance().isKeyPressed(SDL_SCANCODE_SPACE)) {
        int32_t textureHeight;
        SDL_QueryTexture(m_pTexture, nullptr, nullptr, nullptr, &textureHeight);
        const auto totalRows = static_cast<int32_t>(std::ceil(static_cast<float_t>(textureHeight) / m_height));
        if (m_row + 1 >= totalRows) {
            onComplete();
            return;
        }

        m_row++;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void ScrollableText::draw() {
    int32_t textureWidth;
    int32_t textureHeight;
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

void ScrollableText::clean() {
}

void ScrollableText::onComplete() {
    UIElement::onComplete();
    if (m_pTexture != nullptr) {
        SDL_DestroyTexture(m_pTexture);
    }
}

void ScrollableText::loadTexture() {
    if (m_pFont == nullptr) {
        return;
    }

    SDL_Surface* pSurface = TTF_RenderUNICODE_Blended_Wrapped(m_pFont, 
        reinterpret_cast<const Uint16*>(m_text.c_str()), m_color, m_width);
    m_pTexture = SDL_CreateTextureFromSurface(Game::instance().getRenderer(), pSurface);
    SDL_FreeSurface(pSurface);
}