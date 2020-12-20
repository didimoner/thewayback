#pragma once
#include "Drawable.h"

class Player;
class UIElement;

class UserInterface : public Drawable {

private:
    std::vector<std::shared_ptr<UIElement>> m_uiElements;

public:
    void createTextBox(std::function<void()>& callback);

    void update() override;
    void draw() override;

};