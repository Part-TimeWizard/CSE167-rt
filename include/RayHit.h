#include <glm/glm.hpp>
#include "Primitive.h" 

#ifndef __RAYHIT_H__
#define __RAYHIT_H__

class RayHit {
public:
    Ray ray;            //  ray in consideration
    Primitive solid;    //  first solid hit by ray
    glm::vec3 h_pos;    //  intersection point vector
    glm::vec3 normal;   //  intersection normal vector
    
    RayHit(); 
    RayHit(Ray ray, Primitive solid, glm::vec3 point); 
    ~RayHit(); 

    Ray getRay();
    Primitive getPrim();
    glm::vec3 getPos();
    glm::vec3 getNorm();
};

#endif

