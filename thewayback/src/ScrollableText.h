#pragma once
#include "UIElement.h"
#include <SDL.h>
#include <SDL_ttf.h>

class ScrollableText : public UIElement {

public:
    struct InitParams {
        GameObject::InitParams gameObjectInitParams;
        std::string fontId;
        SDL_Color color;
        std::wstring text;
    };

private:
    TTF_Font* m_pFont = nullptr;
    std::wstring m_text;
    SDL_Texture* m_pTexture = nullptr;
    uint8_t m_row = 0;
    SDL_Color m_color = {0, 0, 0};

public:
    void init(const InitParams& initParams);
    void update() override;
    void draw() override;
    void clean() override;

private:
    void loadTexture();
    void onComplete() override;

};
