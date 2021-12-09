/**
 *  Sphere.cpp
 *  
 *  
 */
#include "Sphere.h"

Sphere::Sphere(glm::vec3 center, float radius, glm::mat4 t, glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh) {
    c = center; 
    r = radius; 
    transform = t; 
}

void Sphere::transform(glm::vec3) {
    return;
}

glm::vec4 Sphere::checkHit(Ray ray) {
    glm::vec3 p0 = ray.ori;
    glm::vec3 d = glm::normalize(ray.dir);

    // Transform ray to sphere's space
    glm::vec4 pTransformed0 = glm::inverse(transform) * glm::vec4(p0,1.0f);
    glm::vec4 dTransformed = glm::inverse(glm::mat3(transform)) * d;
    
    glm::vec3 pmc = p0 - c;                 // p - c 
    float dpc = glm::dot((-1.0 * d), pmc);  // dot product of -d and p0-c 
    float t;                                // t used for intersection 

    // inside sqrt test 
    float sqrt = std::powf(glm::dot(d, pmc), 2.0f) - 
    std::powf(std::abs(pmc), 2) + std::powf(r, 2); 

    // intersection test 
    if (sqrt <= 0) { return glm::vec4(q, 0); }
    else { 
        float t1 = dpc + std::sqrtf(sqrt); 
        float t2 = dpc - std::sqrtf(sqrt); 
        if (t1 < t2 && t1 > 0) { t = t1; }  // find smaller and positive t 
        else if (t2 > 0) { t = t2; }
    }

    glm::vec3 q = p0 + t * d; 
    glm::vec3 n = glm::normalize(q - c); 

    // Transform back
    glm::vec4 qTransformed = transform * glm::vec4(q,1);
    glm::vec3 nTransformed = glm::transpose(glm::mat3(transform))*n;
    nTransformed = glm::normalize(nTransformed);

    t = std::abs(qTransformed - nTransformed); 
}