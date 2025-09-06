#pragma once

#include <cmath>

namespace linal {

class Vector {
  public:
    Vector( float x, float y, float z ) : x( x ), y( y ), z( z ) {}

    float
    getLen() const
    {
        return sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
    }

    float
    getCos( const Vector& that ) const
    {
        return *this * that / ( getLen() * that.getLen() );
    }

    // Module of vectorMul
    float
    operator&&( const Vector& that ) const
    {
        return getLen() * that.getLen() * sin( acos( getCos( that ) ) );
    }

    // Sum of vectors
    Vector
    operator+( const Vector& that ) const
    {
        return { this->x + that.x, this->y + that.y, this->z + that.z };
    }

    // Diff of vectors
    Vector
    operator-( const Vector& that ) const
    {
        return { this->x - that.x, this->y - that.y, this->z - that.z };
    }

    // Scalar mul of vectors
    int
    operator*( const Vector& that ) const
    {
        return ( this->x * that.x ) + ( this->y * that.y ) + ( this->z * that.z );
    }

    // Normalizing the vector
    void
    operator~()
    {
        int len = getLen();

        x /= len;
        y /= len;
        z /= len;
    }

    float x;
    float y;
    float z;
};

} // namespace linal
