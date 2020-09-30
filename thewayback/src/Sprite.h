#pragma once
#include "GameObject.h"

class Sprite : public GameObject {

protected:
    uint8_t m_row = 0;
    uint8_t m_frame = 0;
    std::string m_textureId;

public:
    Sprite() : GameObject() {
    }

    virtual ~Sprite() {
    }

    virtual void init(float x, float y, int w, int h, std::string textureId);
    void update() override;
    void draw() override;

    void clean() override {
    }

};
