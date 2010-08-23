#ifndef VECTOR_MATH
#define VECTOR_MATH

#include <math.h>
#include "SFML/System.hpp" // for vector2f
#include "MyRect.h"

// not too much yet but it helps alot
/// static class members, access by using VectorMath::GetLength() exc...
namespace cell
{
    class VectorMath
    {
    public:
        inline static sf::Vector2f GetVelocity(float length, float angle)
        {
            sf::Vector2f velocity;
            velocity.x = (length*(cosf(angle)));
            velocity.y = (length*(sinf(angle)));
            return velocity;
        }


        inline static float GetAngle(const sf::Vector2f &point1, const sf::Vector2f& point2)
        {
            float y = point2.y - point1.y;
            float x =  point2.y - point1.x;
            if( x > 0 )
                return atanf(y/x);
            else
                return atan2f(y,x);
        }


        inline static float GetLength(const sf::Vector2f& point1, const sf::Vector2f& point2)
        {
            return sqrtf(powf(point2.x-point1.x,2) + powf(point2.y-point1.y,2));
        }


        inline static float GetAngle(const sf::Vector2f& vector)
        {
            if(vector.x > 0)
                return atanf(vector.x/vector.y);
            else
                return atan2f(vector.x, vector.y);
        }


        static float GetRotationAngle(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
        {
            return ((atan2f(vector2.x - vector1.x, vector2.y - vector1.y) * 180 / 3.14593)+180);
        }

        inline static sf::Vector2f GetBulletPath(sf::Vector2f& vec1, sf::Vector2f& vec2)
        {
            float length = GetLength(vec1, vec2);
            return sf::Vector2f((vec2.x/length)*7-(vec1.x/length)*7, (vec2.y/length)*7-(vec1.y/length)*7);
        }

        inline static sf::Vector2f GetPlayerPath(sf::Vector2f& vec1, sf::Vector2f& vec2)
        {
            float length = GetLength(vec1, vec2);
            return sf::Vector2f((vec2.x/length)-(vec1.x/length), (vec2.y/length)-(vec1.y/length));
        }


        inline static float GetLength(const sf::Vector2f& vector)
        {

            return sqrtf(powf(vector.x,2)+ powf(vector.y,2));
        }


        inline static void Normalize(sf::Vector2f &vector)
        {
            float len = GetLength(vector);
            vector.x /= len;
            vector.y /= len;
        }


        inline static float DotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
        {
            return (vec1.x * vec2.x + vec1.y * vec2.y);
        }
    };
    typedef VectorMath Vect;
}
/// the typedef is so it can look like this Vect::GetVelocity() you can typedef to make it look like what you want

/// you could also create an instance but using static access is the best way


#endif
