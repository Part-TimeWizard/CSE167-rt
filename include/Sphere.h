/**
 *  Sphere.h
 *  
 *  
 */
#include "Primitive.h"
#pragma once

class Sphere : public Primitive {

    public:
        Sphere(float x, float y, float z, float r){ position = glm::vec3(x,y,z); radius = r; };
        void transform(glm::vec3); 
        void checkHit(glm::vec3);

    private:
        glm::vec3 position; // May need a better way of storing this (start modelview then right multipy w transforms?)
        float radius;
};