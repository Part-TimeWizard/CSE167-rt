#pragma once 

#include <vector> 
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

#include "Ray.h"
//#include "Color.h" 

class Light {
public: 
    // Attributes 
    glm::vec3 color;    // color of light source 
    glm::vec3 atten;    // light attenuations 
    glm::vec3 pos;      // location of point source 
    glm::vec3 dir;      // direction of directional light

    // Constructor
    Light(glm::vec3 color, glm::vec3 attenuation); 

    // Methods 
    virtual float distanceTo(glm::vec3 const &point) const = 0; 
    virtual glm::vec3 colorAt(glm::vec3 const &point) const = 0; 
};  

class PointLight : public Light {
public: 
    // Attributes 
    //glm::vec3 pos;      // Location of point source 

    // Constructor
    PointLight(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation); 

    // Methods 
    float distanceTo(glm::vec3 const &point) const override; 
    glm::vec3 colorAt(glm::vec3 const &point) const override; 
};

class DirectionalLight : public Light {
public: 
    // Attributes 
    //glm::vec3 dir;      // direction to light source 

    // Constructor
    DirectionalLight(glm::vec3 direction, glm::vec3 color, glm::vec3 attenuation); 

    // Methods 
    float distanceTo(glm::vec3 const &point) const override; 
    glm::vec3 colorAt(glm::vec3 const &point) const override;
};