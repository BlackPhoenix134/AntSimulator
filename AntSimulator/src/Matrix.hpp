#pragma once
#include <math.h>       
#include <raylib.h>
struct Matrix2x2
{
private:
    float m00, m01;
    float m10, m11;
public:
    Matrix2x2();
    Matrix2x2(float m00, float m10, float m01, float m11);
    Matrix2x2 transpose();
    Vector2 operator*(Vector2 rhs);
    Matrix2x2 operator*(Matrix2x2 rhs);
}