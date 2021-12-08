#include "Light.h"

const glm::vec3 atten_default(1, 0, 0); 

Light::Light(glm::vec3 color, glm::vec3 attenuation) {
    color = color; 
    atten = attenuation; 
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation)
    : Light(color, attenuation) {
    pos = position; 
}

float PointLight::distanceTo(glm::vec3 const &point) const {
    return glm::distance(pos, point); 
}

glm::vec3 PointLight::colorAt(glm::vec3 const &point) const {

    // point light source has unique way to calculate color at point dist away 
    // attenuation(constant, linear, quadratic) 
    float dist = distanceTo(point); 
    float ptIntensity = atten[0] + atten[1] * dist + atten[2] * dist * dist; 

    return color / ptIntensity;  
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, glm::vec3 attenuation) 
    : Light(color, attenuation) {
    dir = glm::normalize(direction); 
}

float DirectionalLight::distanceTo(glm::vec3 const &point) const {

    // directional light has no origin, so distance is always "infinity" 
    return FLT_MAX; 
}

glm::vec3 DirectionalLight::colorAt(glm::vec3 const &point) const {
    
    // all light from directional light has same intensity regardless of reference
    return color; 
}

