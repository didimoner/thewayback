#pragma once
#include <SDL.h>
#include "Vector2f.h"

enum MouseButton {
	LEFT = 0, MIDDLE, RIGHT
};

class InputHandler {

private:
	InputHandler();
	~InputHandler();

	bool m_mouseButtonStates[3];
	Vector2f* m_pMousePosition;
	const Uint8* m_keystates;

	static InputHandler* s_pInstance;

public:
	InputHandler(const InputHandler&) = delete;
	InputHandler& operator=(const InputHandler&) = delete;

	static InputHandler* instance() {
		if (s_pInstance == nullptr) {
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}

	// ----------------------------------

	void update();
	void clean();

	bool isKeyPressed(SDL_Scancode key) const;
	bool isMouseButtonPressed(MouseButton button) const { return m_mouseButtonStates[button]; }
	const Vector2f* const getMousePosition() const { return m_pMousePosition; }

private:
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	void onKeyboardUpdate();

};