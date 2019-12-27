#include "plane.h"
#include "matrix.h"
#include <cmath>
std::vector<double> plane::get_collisions(ray &r)
{
    /* Collision! Lets assume this is a 1x1 rectangle
       starting at the origin and on the xy plane.
       Instead of transforming the object, lets apply
       the inverse transformation on the ray */
    std::vector<double> collisions;
    /* Transform ray
       Rotation
    */
    //Translation: From origin to actual trcorner
//    ray m_ray = r.get_translated(trcorner.x, -trcorner.y, -trcorner.z);
    ray m_ray = r.get_transformed(translation(trcorner.x, trcorner.y, trcorner.z).inverse());
    //Rotation: From 0,0,1 to normal
    //X axis
    double angle = -PI/2 - acos(normal.y);
    m_ray = m_ray.get_transformed(rotate_x(angle).inverse());
    //Y axis
    angle = PI/2 + acos(normal.x);
    m_ray = m_ray.get_transformed(rotate_y(angle).inverse());

    /* Get collision (if any!) */
    double t = -(m_ray.origin.z/m_ray.direction.z);
    tuple pos = m_ray.position(t);

    if ((is_equal(width,0) || ((pos.x > 0) && (pos.x < width))) && (is_equal(height,0) || ((pos.y > 0) && (pos.y < height))))
        collisions.push_back(t);

    return collisions;
}

ray plane::get_unary_normal_at(tuple &point)
{
    return ray{point, normal};
}
