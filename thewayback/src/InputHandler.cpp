#include "pch.h"
#include "InputHandler.h"
#include <SDL.h>
#include "Game.h"

std::unique_ptr<InputHandler> InputHandler::s_pInstance;


InputHandler::InputHandler() {
	m_mouseButtonStates[MouseButton::LEFT] = false;
	m_mouseButtonStates[MouseButton::MIDDLE] = false;
	m_mouseButtonStates[MouseButton::RIGHT] = false;
	m_mouseButtonStates[1] = false;
}

void InputHandler::update() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				Game::instance().quit();
				break;

			case SDL_MOUSEMOTION:
				onMouseMove(event);
				break;

			case SDL_MOUSEBUTTONDOWN:
				onMouseButtonDown(event);
				break;

			case SDL_MOUSEBUTTONUP:
				onMouseButtonUp(event);
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				onKeyboardUpdate();
				break;

			default:
				break;
		}
	}
}

void InputHandler::onMouseMove(SDL_Event& event) {
	m_mousePosition.set((float)event.motion.x, (float)event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE) {
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT) {
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		m_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE) {
		m_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT) {
		m_mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onKeyboardUpdate() {
	m_keystates = SDL_GetKeyboardState(NULL);
}

bool InputHandler::isKeyPressed(SDL_Scancode key) const {
	if (m_keystates == nullptr) {
		return false;
	}

	return m_keystates[key] == 1;
}

bool InputHandler::isMouseButtonPressed(MouseButton button) const { return m_mouseButtonStates[button]; }

Vector2f InputHandler::getMousePosition() const { return m_mousePosition; }