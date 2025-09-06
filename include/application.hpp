#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector3.hpp>
#include "camera.hpp"
#include "config.hpp"
#include "sphere.hpp"
#include "light.hpp"

namespace application {

class Application {
  public:
    Application()
        : width_( config::WindowWidth ), height_( config::WindowHeight ),
          sphere_( { 0, 0, 50 }, 10 ), camera_( { 0, 0, 0 }, M_PI_2 ),
          window_( sf::VideoMode( config::WindowWidth, config::WindowHeight ),
                   config::Title,
                   sf::Style::Close )
    {
        window_.setFramerateLimit( 60 );
        pixels_.resize( width_ * height_ );
    }

    void
    run()
    {
        while ( window_.isOpen() )
        {

            handleEvents();
            render();
            window_.clear();
            draw();
            window_.display();
        }
    }

  private:
    sf::RenderWindow            window_;
    std::vector<sf::Vertex>     pixels_;
    objects::Sphere             sphere_;
    objects::Camera             camera_;
    std::vector<objects::Light> lights_;

    uint width_;
    uint height_;

    const sf::Color backgorund_color_ = { 10, 10, 10 };

    void
    handleEvents()
    {
        sf::Event event;
        while ( window_.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window_.close();
            }
        }
    }

    void
    render()
    {
        for ( uint row = 0; row < height_; row++ )
        {
            for ( uint col = 0; col < width_; col++ )
            {
                const linal::Vector world_coords =
                    camera_.screenToWorld( row, col, height_, width_ );

                bool is_sphere = sphere_.rayIntersect( linal::Line( world_coords, { 0, 0, 0 } ) );

                if ( !is_sphere )
                {
                    pixels_[( row * width_ ) + col] =
                        sf::Vertex( sf::Vector2f( col, row ), backgorund_color_ );
                    continue;
                }

                const sf::Color color = sphere_.color;

                for ( auto light : lights_ )
                {
                }

                pixels_[( row * width_ ) + col] = sf::Vertex( sf::Vector2f( col, row ), color );
            }
        }
    }

    void
    draw()
    {
        window_.draw( pixels_.data(), pixels_.size(), sf::Points );
    }
};

} // namespace application
