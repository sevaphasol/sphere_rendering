#pragma once

#include <SFML/Graphics.hpp>

#include "geometry/vector.hpp"
#include "geometry/line.hpp"

namespace render {

class Camera {
  public:
    Camera( const geometry::Vector& pos, float fov );

    void
    Rotate( float hor_angle, float ver_angle );

    geometry::Line
    TraceRay( uint px_y, uint px_x, uint scr_height, uint scr_width ) const;

    void
    Move( const geometry::Vector& delta );

    geometry::Vector
    GetPos() const;

    geometry::Vector
    GetHorOrt() const;

    geometry::Vector
    GetVerOrt() const;

    geometry::Vector
    GetFwdOrt() const;

    float
    GetFov() const;

  private:
    void
    Rotate( float angle, geometry::Vector& ort );

  private:
    geometry::Vector pos_;
    geometry::Vector hor_ort_;
    geometry::Vector ver_ort_;
    geometry::Vector fwd_ort_;
    float            fov_;
};

} // namespace render
