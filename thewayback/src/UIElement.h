#pragma once
#include "pch.h"
#include "GameObject.h"

class UIElement : public GameObject {

protected:
    bool m_active = true;
    std::function<void()> m_callback = []() {};

public:
    void setCallback(std::function<void()>& callback) {
        m_callback = std::move(callback);
    }

    bool isActive() const {
        return m_active;
    }

protected:
    virtual void onComplete() {
        m_active = false;
        m_callback();
    }

};
