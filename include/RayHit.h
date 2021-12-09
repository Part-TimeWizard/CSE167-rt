#include <glm/glm.hpp>
#include "Primitive.h" 
#include "Ray.h"

#ifndef __RAYHIT_H__
#define __RAYHIT_H__

class RayHit {
public:
    Ray ray;            //  ray in consideration
    Primitive* solid;    //  first solid hit by ray
    glm::vec3 pos;    //  intersection point vector
    glm::vec3 normal;   //  intersection normal vector
    
    RayHit(); 
    RayHit(Ray m_ray, Primitive* solid, glm::vec3 point); 
    ~RayHit(); 
};

#endif

