#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector3.hpp>

#include "geometry/vector.hpp"
#include "geometry/sphere.hpp"

#include "render/camera.hpp"
#include "render/light.hpp"

namespace render {

class Renderer {
  public:
    Renderer();

    void
    Run();

    void
    AddLight( float x, float y, float z, float intensity );

    void
    AddSphere( float x, float y, float z, float radius, const sf::Color& color );

  private:
    void
    HandleEvents();

    sf::Color
    GetLightsDep( const geometry::Vector& point );

    sf::Color
    CalcPixelColor( uint row, uint col );

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
