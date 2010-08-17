#include "Trig.h"
#include <iostream>
#define PI 3.141593

using namespace cell;

sf::Vector2f VectorMath::GetVelocity(float length, float angle)
{
    sf::Vector2f velocity;
    velocity.x = (length*(cosf(angle)));
    velocity.y = (length*(sinf(angle)));
    return velocity;
}

// gets the angle for movement, use GetRotationAngle for rotation
float VectorMath::GetAngle(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    float y = point2.y - point1.y;
    float x =  point2.y - point1.x;
    if( x > 0 )
        return atanf(y/x);
    else
        return atan2f(y,x);

}


// gets the angle offset of a single point represented by taking the offset of the x and y axis
float VectorMath::GetAngle(const sf::Vector2f& vector)
{
    if(vector.x > 0)
        return atanf(vector.x/vector.y);
    else
        return atan2f(vector.x, vector.y);
}


// I GOT ROTATION TO WORK
float VectorMath::GetRotationAngle(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    return ((atan2f(point2.x - point1.x, point2.y - point1.y) * 180 / 3.14593)+180); // adding 180 is to rotate acroding to the top not bottom
    // i dont use the define PI because someone told me it was faster not to
}

// sets the length of the vector to 1 but the angle is still the same
void VectorMath::Normalize(sf::Vector2f &vector)
{
    float len = GetLength(vector);
    vector.x /= len;
    vector.y /= len;
}

float DotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
    return (vec1.x * vec2.x + vec1.y * vec2.y);
}

// takes the offset of both the x's and y's to get the length
float VectorMath::GetLength(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    return sqrtf(powf(point2.x-point1.x,2) + powf(point2.y-point1.y,2));
}

// takes the offset of the x and y to get the length
float VectorMath::GetLength(const sf::Vector2f &vector)
{
    return sqrtf(powf(vector.x,2)+ powf(vector.y,2));
}

