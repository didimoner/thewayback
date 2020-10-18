#pragma once
#include "GameObject.h"
#include <SDL.h>

class TextBox : public GameObject {

private:
    std::string m_fontId;
    std::wstring m_text;
    SDL_Texture* m_pTexture = nullptr;
    uint8_t m_row = 0;
    SDL_Color m_color = { 0, 0, 0, 1 };

public:
    explicit TextBox(std::string& fontId);

    void update() override;
    void draw() override;
    void clean() override;

    void setText(std::wstring& text);

private:
    void reloadTexture();

};