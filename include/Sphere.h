/**
 *  Sphere.h
 *  
 *  
 */
#include "Primitive.h"

#include <glm/glm.hpp> 
#include <math.h> 
#include <algorithm> 
#pragma once

class Sphere : public Primitive {

    public:
        Sphere(glm::vec3 center, float radius, glm::mat4 t, glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh)
            : Primitive(a,sp,d,e,sh){ c = center; transform = t; r = radius; };
        glm::vec4 checkHit(Ray r);

    private:
        glm::vec3 c; // May need a better way of storing this (start modelview then right multipy w transforms?)
        float r;
        glm::mat4 transform; // Transformation vector for the sphere
};