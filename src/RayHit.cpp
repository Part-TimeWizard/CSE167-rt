#include "RayHit.h"

/*
** Constructors
*/

RayHit::RayHit() {}
RayHit::~RayHit() {} 

RayHit::RayHit (Ray ray, Primitive* intSolid, glm::vec3 intPoint) {
    ray = ray;
    solid = intSolid;
    pos = intPoint;
    normal = glm::normalize(intPoint);
}
