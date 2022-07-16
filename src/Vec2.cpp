#include "Vec2.h"

Vec2::Vec2(float x, float y){
    this->x = x;
    this->y = y;
}

Vec2 Vec2::GetRotated(float ang){
    float cos_a = cos(ang);
    float sin_a = sin(ang);
    int temp_x = this->x;
    int temp_y = this->y;

    this->x = cos_a*temp_x - sin_a*temp_y;
    this->y = sin_a*temp_x + cos_a*temp_y;

    return {this->x, this->y};

}

Vec2 Vec2::operator+(const Vec2& sum){
    Vec2 soma;
    soma.x = (this->x + sum.x);
    soma.y = (this->y + sum.y);
    return soma;
}