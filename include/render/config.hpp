#pragma once

#include <sys/types.h>
#include <SFML/Graphics.hpp>

namespace render {

class Config {
  public:
    static constexpr const char* const Title        = "SphereRendering";
    static constexpr uint              WindowWidth  = 1200.0f;
    static constexpr uint              WindowHeight = 800.0f;
    static constexpr float             CameraFov    = 1.05;
    static constexpr float             WasdScale    = 0.1f;
    static const sf::Color             BackgroundColor;
};

inline const sf::Color Config::BackgroundColor = sf::Color( 16, 16, 16 );

} // namespace render
