#pragma once
#include <cmath>
// simple struct to manage Float Vectors

struct Vector2D {

  public:
    float x = 0;
    float y = 0;

    Vector2D() = default; // default constructor
    Vector2D(float x1, float y1) : x(x1), y(y1) {}
    ~Vector2D() = default;

    bool operator==(const Vector2D &v2) const { return this->x == v2.x && this->y == v2.y; }

    Vector2D operator+(const Vector2D &v2) const { return {this->x + v2.x, this->y + v2.y}; }

    Vector2D operator-(const Vector2D &v2) const { return {this->x - v2.x, this->y - v2.y}; }

    Vector2D operator+=(const Vector2D &v2) {
        this->x += v2.x;
        this->y += v2.y;
        return *this;
    }

    Vector2D operator-=(const Vector2D &v2) {
        this->x -= v2.x;
        this->y -= v2.y;
        return *this;
    }
    // Scalar *Vector Multiplication
    Vector2D operator*(float scalar) const { return Vector2D{x * scalar, y * scalar}; }

    Vector2D &operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    // this function returns the magnitude of the vector Squared(better performance)
    float getMagnitudeSq() const { return (x * x) + (y * y); }

    float getMagnitude() const { // get the magnitude

        return std::sqrt(getMagnitudeSq());
    }

    // this function returns the unit vector but DOES NOT normalized the vector
    Vector2D getNormalized() const {
        float mag = getMagnitude();
        if (mag == 0.0f) {
            return Vector2D{0, 0};
        } else {
            float invMag = 1.0f / mag;
            return Vector2D(x * invMag, y * invMag);
        }
    }
    // this functions return the inverse vector
    Vector2D operator-() const { return Vector2D{-x, -y}; }
    Vector2D &Inverse() {
        x = -x;
        y = -y;
        return *this;
    }
};
