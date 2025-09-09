#pragma once

#include <sys/types.h>
#include <SFML/Graphics.hpp>

#include "geometry/vector.hpp"

#include "render/light.hpp"
#include "geometry/sphere.hpp"

namespace render {
namespace config {

const char* const Title        = "SphereRendering";
constexpr uint    WindowWidth  = 1000.0F;
constexpr uint    WindowHeight = 1000.0F;

const float CameraFov = 1.05;

const sf::Color BackgroundColor = sf::Color::Magenta;

const render::Light Lights[] = { render::Light( { 3, 3, 4.5F }, 0.2 ) };

const geometry::Sphere Spheres[] = { geometry::Sphere( { 0, 0, 10 }, 2 ) };

} // namespace config
} // namespace render
