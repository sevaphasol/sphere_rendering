#include "geometry/vector.hpp"

namespace geometry {

Vector::Vector( float x, float y, float z ) : x( x ), y( y ), z( z ) {}

bool
Vector::Valid() const
{
    return !( std::isnan( x ) || std::isnan( y ) || std::isnan( z ) );
}

float
Vector::GetLen() const
{
    return sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
}

float
Vector::operator,( const Vector& that ) const
{
    return ( this->x * that.x ) + ( this->y * that.y ) + ( this->z * that.z );
}

Vector
Vector::operator+( const Vector& that ) const
{
    return { this->x + that.x, this->y + that.y, this->z + that.z };
}

Vector
Vector::operator-( const Vector& that ) const
{
    return { this->x - that.x, this->y - that.y, this->z - that.z };
}

void
Vector::operator+=( const Vector& that )
{
    this->x += that.x;
    this->y += that.y;
    this->z += that.z;
}

void
Vector::operator-=( const Vector& that )
{
    this->x -= that.x;
    this->y -= that.y;
    this->z -= that.z;
}

Vector
Vector::operator+( float scalar ) const
{
    return Vector( this->x + scalar, this->y + scalar, this->z + scalar );
}

Vector
Vector::operator-( float scalar ) const
{
    return Vector( this->x - scalar, this->y - scalar, this->z - scalar );
}

Vector
Vector::operator*( float scalar ) const
{
    return Vector( this->x * scalar, this->y * scalar, this->z * scalar );
}

void
Vector::operator+=( float scalar )
{
    this->x += scalar;
    this->y += scalar;
    this->z += scalar;
}

void
Vector::operator-=( float scalar )
{
    this->x -= scalar;
    this->y -= scalar;
    this->z -= scalar;
}

void
Vector::operator*=( float scalar )
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
}

float
CalcCos( const Vector& v1, const Vector& v2 )
{
    return ( v1, v2 ) / ( v1.GetLen() * v2.GetLen() );
}

float
CalcSin( const Vector& v1, const Vector& v2 )
{
    return sin( acos( CalcCos( v1, v2 ) ) );
}

float
CalcVecMulModule( const Vector& v1, const Vector& v2 )
{
    return v1.GetLen() * v2.GetLen() * CalcSin( v1, v2 );
}

} // namespace geometry
