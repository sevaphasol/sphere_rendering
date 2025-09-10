#include "render/renderer.hpp"
#include "geometry/vector.hpp"
#include "render/config.hpp"
#include <iostream>

namespace render {

Renderer::Renderer()
    : width_( Config::WindowWidth ), height_( Config::WindowHeight ),
      camera_( { 0, 0, 0 }, Config::CameraFov ),
      window_( sf::VideoMode( Config::WindowWidth, Config::WindowHeight ),
               Config::Title,
               sf::Style::Close ),
      pixels_( Config::WindowWidth * Config::WindowHeight ),
      backgorund_color_( Config::BackgroundColor ) {};

void
Renderer::Run()
{
    while ( window_.isOpen() )
    {
        HandleEvents();
        Render();
        Draw();
    }
}

void
Renderer::AddLight( float x, float y, float z, float intensity )
{
    lights_.push_back( Light( geometry::Vector( x, y, z ), intensity ) );
}

void
Renderer::AddSphere( float x, float y, float z, float radius, const sf::Color& color )
{
    spheres_.push_back( geometry::Sphere( geometry::Vector( x, y, z ), radius, color ) );
}

void
Renderer::HandleEvents()
{
    sf::Event event;
    while ( window_.pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed )
        {
            window_.close();
        }
    }

    int move_left     = int( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) );
    int move_right    = int( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) );
    int move_forward  = int( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) );
    int move_backward = int( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) );
    int move_up       = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) );
    int move_down     = int( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) );
    int turn_left     = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) );
    int turn_right    = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) );
    int turn_up       = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) );
    int turn_down     = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) );

    camera_.Move( camera_.GetHorOrt() * ( move_right - move_left ) * Config::MoveScale +
                  camera_.GetVerOrt() * ( move_up - move_down ) * Config::MoveScale +
                  camera_.GetFwdOrt() * ( move_forward - move_backward ) * Config::MoveScale *
                      ( -1 ) );
    camera_.Rotate( ( turn_right - turn_left ) * Config::RotateScale,
                    ( turn_up - turn_down ) * Config::RotateScale );
}

sf::Color
Renderer::CalcLightsLumacy( const geometry::Vector& point, const geometry::Vector& normal )
{
    float lights_dep = 0;

    for ( const auto& light : lights_ )
    {
        lights_dep += light.CalcLumacy( point - camera_.GetPos(), point, normal );
    }

    sf::Uint8 lumacy = std::clamp( lights_dep * 255.f, 0.f, 255.f );

    return sf::Color( lumacy, lumacy, lumacy );
}

sf::Color
Renderer::CalcPixelColor( uint row, uint col )
{
    const geometry::Line view_ray = camera_.TraceRay( row, col, height_, width_ );

    for ( const auto& sphere : spheres_ )
    {
        const geometry::Vector point = sphere.GetIntersectionWithLine( view_ray );

        if ( point.Valid() )
        {
            return sphere.GetColor() + CalcLightsLumacy( point, point - sphere.GetCenter() );
        }
    }

    return backgorund_color_;
}

void
Renderer::Render()
{
#pragma omp parallel for
    for ( uint row = 0; row < height_; row++ )
    {
        for ( uint col = 0; col < width_; col++ )
        {
            sf::Vector2f pos   = sf::Vector2f( col, row );
            sf::Color    color = CalcPixelColor( row, col );

            pixels_[row * width_ + col] = sf::Vertex( pos, color );
        }
    }
}

void
Renderer::Draw()
{
    window_.clear();
    window_.draw( pixels_.data(), pixels_.size(), sf::Points );
    window_.display();
}

} // namespace render
