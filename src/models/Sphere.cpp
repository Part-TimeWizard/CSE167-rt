/**
 *  Sphere.cpp
 *  
 *  
 */
#include "Sphere.h"

glm::vec4 Sphere::checkHit(Ray ray) {
    glm::vec3 p0 = ray.ori;
    glm::vec3 d = glm::normalize(ray.dir);

    // Transform ray to sphere's space
    glm::vec4 pTransformed0 = glm::inverse(transform) * glm::vec4(p0,1.0f);
    glm::vec3 dTransformed = glm::inverse(glm::mat3(transform)) * d;
    
    // (o + td - c)^2 - R^2 = 0
    // at^2 + bt + c = 0 where 
    // a = d dot d 
    // b = 2 * (p0 - c) dot d 
    // c = (p0 - c) dot (p0 - c) - R^2 
    float a = glm::dot(d, d); 
    float b = 2 * glm::dot((p0 - c), d); 
    float c = glm::dot((p0 - c), (p0 - c)) - std::powf(r, 2.0f); 

    // Quadratic formula for t 
    float t1 = (-1.0f * b + std::sqrt(std::pow(b, 2) - 4 * a * c)) / (2 * a); 
    float t2 = (-1.0f * b - std::sqrt(std::pow(b, 2) - 4 * a * c)) / (2 * a); 

    if (t1 > t2) {
        // swap variables if first is bigger 
        // we want smaller positive t 
        float temp = t1; 
        t1 = t2; 
        t2 = temp; 
    }
    // no intersect cases 
    if (t2 < 0) { return glm::vec4(0.0f); } 
    if (t1 < 0) { return glm::vec4(0.0f); }

    // position of intersection 
    glm::vec3 q = p0 + t1 * d; 
    glm::vec3 n = glm::normalize(q - c); 

    // Transform back
    glm::vec4 qTransformed = transform * glm::vec4(q[0], q[1], q[2], 1);
    glm::vec3 nTransformed = glm::transpose(glm::mat3(transform)) * n;
    nTransformed = glm::normalize(nTransformed);

    glm::vec3 newQ(qTransformed[0], qTransformed[1], qTransformed[2]); 

    glm::vec3 newT = glm::abs(newQ - p0); 
    glm::vec4 finT(newT[0], newT[1], newT[2], 1.0f); 
    return finT; 
}