#pragma once

#include <math.h>
#include <sstream>

class Vector2f {

public:
    Vector2f() : m_x(0), m_y(0) {}
    Vector2f(float x, float y) : m_x(x), m_y(y) {}

    float getX() const { return m_x; }
    void setX(float x) { m_x = x; }

    float getY() const { return m_y; }
    void setY(float y) { m_y = y; }

    void set(float x, float y) { m_x = x; m_y = y; }

    float length() const { 
        return sqrt(pow(m_x, 2) + pow(m_y, 2));
    }

    Vector2f operator+(const Vector2f& other) const {
        return Vector2f(m_x + other.m_x, m_y + other.m_y);
    }
    Vector2f& operator+=(const Vector2f other) {
        m_x += other.m_x;
        m_y += other.m_y;

        return *this;
    }

    Vector2f operator*(float scalar) const {
        return Vector2f(m_x * scalar, m_y * scalar);
    }
    Vector2f& operator*=(float scalar) {
        m_x *= scalar;
        m_y *= scalar;

        return *this;
    }

    Vector2f operator-(const Vector2f& other) const {
        return Vector2f(m_x - other.m_x, m_y - other.m_y);
    }
    Vector2f& operator-=(const Vector2f& other) {
        m_x -= other.m_x;
        m_y -= other.m_y;

        return *this;
    }

    Vector2f operator/(float scalar) const {
        return Vector2f(m_x / scalar, m_y / scalar);
    }
    Vector2f& operator/=(const Vector2f& other) {
        m_x /= other.m_x;
        m_y /= other.m_y;

        return *this;
    }

    void normalize() {
        float l = length();
        if (l > 0) {
            (*this) *= 1 / l;
        }
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "(" << m_x << ", " << m_y << ")";
        return ss.str();
    }

private:
    float m_x;
    float m_y;

};