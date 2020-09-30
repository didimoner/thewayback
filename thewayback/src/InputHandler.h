#pragma once
#include <SDL.h>
#include "Vector2f.h"

enum MouseButton {
    LEFT = 0,
    MIDDLE,
    RIGHT
};

class InputHandler {

private:
    InputHandler();

    bool m_mouseButtonStates[3];
    Vector2f m_mousePosition;
    const uint8_t* m_keystates = nullptr;

    static std::unique_ptr<InputHandler> s_pInstance;

public:
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;

    static InputHandler& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new InputHandler());
        }
        return *s_pInstance;
    }

    // ----------------------------------

    void update();

    bool isKeyPressed(SDL_Scancode key) const;
    bool isMouseButtonPressed(MouseButton button) const;
    Vector2f getMousePosition() const;

private:
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    void onKeyboardUpdate();

};
