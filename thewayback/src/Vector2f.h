#pragma once
#include <sstream>

class Vector2f {

private:
    float_t m_x;
    float_t m_y;

public:
    Vector2f() : m_x(0), m_y(0) {
    }

    Vector2f(float_t x, float_t y) : m_x(x), m_y(y) {
    }

    float_t getX() const { return m_x; }
    void setX(float_t x) { m_x = x; }

    float_t getY() const { return m_y; }
    void setY(float_t y) { m_y = y; }

    void set(float_t x, float_t y) {
        m_x = x;
        m_y = y;
    }

    float_t length() const {
        return static_cast<float_t>(sqrt(pow(m_x, 2) + pow(m_y, 2)));
    }

    Vector2f operator+(const Vector2f& other) const {
        return {m_x + other.m_x, m_y + other.m_y};
    }

    Vector2f& operator+=(const Vector2f other) {
        m_x += other.m_x;
        m_y += other.m_y;

        return *this;
    }

    Vector2f operator*(float_t scalar) const {
        return {m_x * scalar, m_y * scalar};
    }

    Vector2f& operator*=(float_t scalar) {
        m_x *= scalar;
        m_y *= scalar;

        return *this;
    }

    Vector2f operator-(const Vector2f& other) const {
        return {m_x - other.m_x, m_y - other.m_y};
    }

    Vector2f& operator-=(const Vector2f& other) {
        m_x -= other.m_x;
        m_y -= other.m_y;

        return *this;
    }

    Vector2f operator/(float_t scalar) const {
        return {m_x / scalar, m_y / scalar};
    }

    Vector2f& operator/=(const Vector2f& other) {
        m_x /= other.m_x;
        m_y /= other.m_y;

        return *this;
    }

    void normalize() {
        float_t l = length();
        if (l > 0) {
            (*this) *= 1 / l;
        }
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "(" << m_x << ", " << m_y << ")";
        return ss.str();
    }

};
