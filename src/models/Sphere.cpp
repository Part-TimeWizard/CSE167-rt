/**
 *  Sphere.cpp
 *  
 *  
 */
#include "Sphere.h"

void Sphere::transform(glm::vec3) {
    return;
}

glm::vec4 Sphere::checkHit(Ray r) {
    glm::vec3 p0 = r.ori;
    glm::vec3 d = r.dir;

    // Transform ray to sphere's space
    glm::vec4 pTransformed0 = glm::inverse(transform) * glm::vec4(p0,1.0f);
    glm::vec4 dTransformed = glm::inverse(glm::mat3(transform)) * d;
    
    // sphere intersect test

    // Transform back
    glm::vec3 qTransformed
    glm::vec3 nTransformed

    return glm::vec4(0,0,0,0);
}