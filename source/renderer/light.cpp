#include "render/light.hpp"

namespace render {

Light::Light( geometry::Vector position, float intensity )
    : position( position ), intensity( intensity ) {};

} // namespace render
