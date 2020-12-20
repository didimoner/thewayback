#pragma once
#include "UIElement.h"
#include <SDL.h>

class Text : public UIElement {

private:
    std::string m_fontId;
    std::wstring m_text;
    SDL_Texture* m_pTexture = nullptr;
    uint8_t m_row = 0;
    SDL_Color m_color = { 255, 0, 0 };
    std::function<void()> m_callback = []() {};

public:
    explicit Text(std::string& fontId);

    void update() override;
    void draw() override;
    void clean() override;

    void setText(std::wstring& text);
    void setCallback(std::function<void()>& callback);

private:
    void reloadTexture();
    void onComplete();

};