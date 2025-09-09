#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector3.hpp>

#include "geometry/vector.hpp"
#include "geometry/sphere.hpp"

#include "render/camera.hpp"
#include "render/light.hpp"

namespace render {

class Screen {
  public:
    Screen();

    void
    Run();

    void
    AddLight( const Light& light );

    void
    AddSphere( const geometry::Sphere& sphere );

  private:
    void
    HandleEvents();

    static float
    getDiffuseLightDep( geometry::Vector& normal, geometry::Vector& light_ray, float intensity );

    static float
    getGlareLightDep( geometry::Vector& normal,
                      geometry::Vector& view,
                      geometry::Vector& light_ray,
                      float             intensity );

    sf::Color
    getLightsDep( const geometry::Vector& point );

    sf::Color
    calcPixelColor( uint row, uint col );

    void
    Render();

    void
    Draw();

  private:
    sf::RenderWindow              window_;
    std::vector<sf::Vertex>       pixels_;
    std::vector<geometry::Sphere> spheres_;
    std::vector<Light>            lights_;
    Camera                        camera_;

    uint width_;
    uint height_;

    const sf::Color backgorund_color_;
};

} // namespace render
