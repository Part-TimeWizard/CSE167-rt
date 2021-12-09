#include "RayHit.h"

/*
** Constructors
*/

RayHit::RayHit() {}
RayHit::~RayHit() {} 

RayHit::RayHit(Ray m_ray, Primitive* intSolid, glm::vec3 intPoint) {
    ray.dir = -1.0f * m_ray.dir;                         // ray that hit 
    solid = intSolid;                   // solid hit by ray 
    pos = intPoint;                     // point of intersection 
    normal = glm::normalize(intPoint);  // surface normal 
}
