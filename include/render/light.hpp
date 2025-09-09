#pragma once

#include <SFML/Graphics.hpp>
#include "geometry/vector.hpp"

namespace render {

class Light {
  public:
    Light( const geometry::Vector& position, float intensity );

    float
    CalcLumacy( const geometry::Vector& view,
                const geometry::Vector& point,
                const geometry::Vector& normal ) const;

  private:
    float
    CalcDiffuseLumacy( const geometry::Vector& light_ray, const geometry::Vector& normal ) const;

    float
    CalcGlareLumacy( const geometry::Vector& light_ray,
                     const geometry::Vector& normal,
                     const geometry::Vector& view ) const;

  public:
    geometry::Vector position;
    float            intensity;
};

geometry::Vector
CalcReflectedRay( const geometry::Vector& light_ray, const geometry::Vector& normal );

} // namespace render
