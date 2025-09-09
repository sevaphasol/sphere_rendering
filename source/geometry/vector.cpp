#include "geometry/vector.hpp"

#pragma once

#include <cmath>

namespace geometry {

Vector::Vector( float x, float y, float z ) : x( x ), y( y ), z( z ) {}

bool
Vector::isValid() const
{
    return !( std::isnan( x ) || std::isnan( y ) || std::isnan( z ) );
}

float
Vector::getLen() const
{
    return sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
}

float
Vector::getCos( const Vector& that ) const
{
    return ( *this * that ) / ( getLen() * that.getLen() );
}

// Module of vectorMul
float
Vector::operator&&( const Vector& that ) const
{
    return getLen() * that.getLen() * sin( acos( getCos( that ) ) );
}

// Sum of vectors
Vector
Vector::operator+( const Vector& that ) const
{
    return { this->x + that.x, this->y + that.y, this->z + that.z };
}

// Sub of vectors
Vector
Vector::operator-( const Vector& that ) const
{
    return { this->x - that.x, this->y - that.y, this->z - that.z };
}

// Scalar mul of vectors
float
Vector::operator*( const Vector& that ) const
{
    return ( this->x * that.x ) + ( this->y * that.y ) + ( this->z * that.z );
}

// Sum vector on scalar
Vector
Vector::operator+( float scalar ) const
{
    return { this->x + scalar, this->y + scalar, this->z + scalar };
}

// Sum vector on scalar
void
Vector::operator+=( float scalar )
{
    this->x += scalar;
    this->y += scalar;
    this->z += scalar;
}

// Sub vector on scalar
Vector
Vector::operator-( float scalar ) const
{
    return { this->x - scalar, this->y - scalar, this->z - scalar };
}

// Mul vector on scalar
Vector
Vector::operator*( float scalar ) const
{
    return { this->x * scalar, this->y * scalar, this->z * scalar };
}

} // namespace geometry
