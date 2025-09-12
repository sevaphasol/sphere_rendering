#pragma once

#include <SFML/Graphics.hpp>
#include "geometry/vector.hpp"

namespace render {

class Light {
  public:
    Light( const geometry::Vector& pos,
           float                   embedded_intensity,
           float                   diffuse_intensity,
           float                   glare_intensity );

    void
    Move( const geometry::Vector& delta );

    geometry::Vector
    CalcLight( const geometry::Vector& view,
               const geometry::Vector& point,
               const geometry::Vector& normal,
               const sf::Color&        color ) const;

  private:
    geometry::Vector
    CalcEmbeddedLight( const geometry::Vector& color ) const;

    float
    CalcDiffuseLight( const geometry::Vector& light_ray, const geometry::Vector& normal ) const;

    float
    CalcGlareLight( const geometry::Vector& light_ray,
                    const geometry::Vector& normal,
                    const geometry::Vector& view ) const;

  private:
    geometry::Vector pos_;
    float            embedded_intensity_;
    float            diffuse_intensity_;
    float            glare_intensity_;
};

geometry::Vector
CalcReflectedRay( const geometry::Vector& light_ray, const geometry::Vector& normal );

} // namespace render
