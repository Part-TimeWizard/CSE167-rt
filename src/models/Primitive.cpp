/**
 *  Primitive.cpp
 *  
 *  Parent class for Sphere and Triangle, contains material data and virtual class to check for ray intersection.
 */
#include "Primitive.h"

Primitive::Primitive() {
    diffuse = glm::vec3(0,0,0);
    specular = glm::vec3(0,0,0);
    shininess = 0.0f;
    emission = glm::vec3(0,0,0);
    ambient = glm::vec3(0,0,0);
}