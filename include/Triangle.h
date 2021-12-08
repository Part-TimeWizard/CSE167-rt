/**
 *  Triangle.h
 *  
 *  
 */
#include "Primitive.h"
#pragma once

class Triangle : public Primitive {

    public:
        Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3){ position = glm::mat3(v1,v2,v3);};
        void transform(glm::vec3); 
        glm::vec3 checkHit(Ray r);

    private:
        glm::mat3 position; // May need a better way of storing this (start modelview then right multipy w transforms?)
};