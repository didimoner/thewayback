#pragma once
#include "pch.h"
#include "Vector2f.h"
#include "GameObject.h"
#include "Game.h"

class Camera {

private:
    Vector2f m_position;
    const GameObject* m_pGameObject;

public:
    Vector2f getPosition() const {
        return m_position;
    }
    
    void setGameObject(const GameObject* pGameObject) {
        m_pGameObject = pGameObject;
    }

    void update() {
        if (m_pGameObject != nullptr) {
            float x = m_pGameObject->getPosition().getX() 
                - (float)(Game::instance()->getWindowWidth() - m_pGameObject->getWidth()) / 2;
            float y = m_pGameObject->getPosition().getY() 
                - (float)(Game::instance()->getWindowHeight() - m_pGameObject->getHeight()) / 2;

            m_position.set(x, y);
        }
    }

};

