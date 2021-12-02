/**
 *  Primitive.h
 *  
 * 
 */
#include <glm/glm.hpp>
#pragma once

class Primitive {

    private:
        glm::vec4 diffuse;
        glm::vec4 specular;
        float shininess;
        glm::vec4 emission;

    public:
        virtual void checkHit(glm::vec3);

        void setDiffuse(glm::vec3 d){ diffuse = d; };
        void setSpecular(glm::vec3 s){ specular = s; };
};