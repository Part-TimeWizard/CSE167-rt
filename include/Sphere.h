/**
 *  Sphere.h
 *  
 *  
 */
#include "Primitive.h"
#pragma once

class Sphere : public Primitive {

    public:
        Sphere(glm::vec3 p, float r){ position = p; radius = r; };
        void transform(glm::vec3); 
        glm::vec3 checkHit(Ray::Ray r);

    private:
        glm::vec3 position; // May need a better way of storing this (start modelview then right multipy w transforms?)
        float radius;
};