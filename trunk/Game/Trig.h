#ifndef VECTOR_MATH
#define VECTOR_MATH

#include <math.h>
#include "SFML/System.hpp" // for vector2f

// not too much yet but it helps alot
/// static class members, access by using VectorMath::GetLength() exc...
namespace cell
{
    class VectorMath
    {
    public:
        inline static sf::Vector2f GetVelocity(float length, float angle);
        inline static float        GetAngle(const sf::Vector2f &point1, const sf::Vector2f& point2);
        inline static float        GetLength(const sf::Vector2f& point1, const sf::Vector2f& point2);
        inline static float        GetAngle(const sf::Vector2f& vector);
        static float               GetRotationAngle(const sf::Vector2f& vector, const sf::Vector2f& vector2);
        inline static float        GetLength(const sf::Vector2f& vector);
        inline static void         Normalize(sf::Vector2f &vector);
        inline static float        DotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
    };
    typedef VectorMath Vect;
}
/// the typedef is so it can look like this Vect::GetVelocity() you can typedef to make it look like what you want

/// you could also create an instance but using static access is the best way


#endif
