/**
 *  Sphere.h
 *  
 *  
 */
#include "Primitive.h"
#pragma once

class Sphere : public Primitive {

    public:
        Sphere(glm::vec3 p, float r, glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh)
            : Primitive(a,sp,d,e,sh){ position = p; radius = r; };
        void transform(glm::vec3); 
        glm::vec4 checkHit(Ray r);

    private:
        glm::vec3 position; // May need a better way of storing this (start modelview then right multipy w transforms?)
        float radius;
};