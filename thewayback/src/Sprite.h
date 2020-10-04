#pragma once
#include "GameObject.h"

class Sprite : public GameObject {

public:
    struct InitParams {
        GameObject::InitParams gameObjectInitParams;
        uint8_t row = 0;
        uint8_t frame = 0;
        std::string textureId;
    };

protected:
    uint8_t m_row = 0;
    uint8_t m_frame = 0;
    std::string m_textureId;

public:
    void init(const InitParams& initParams);
    void update() override;
    void draw() override;

};
