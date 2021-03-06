/**
 *  Primitive.h
 *  
 *  Parent class for Sphere and Triangle, contains material data and virtual class to check for ray intersection.
 */
#include <glm/glm.hpp>
#include "Ray.h"
#pragma once

class Primitive {

    private:
        float shininess;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 emission;
        glm::vec3 ambient;

    public:
        Primitive(glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh){ ambient = a; specular = sp; diffuse = d; emission = e; shininess = sh;};
        Primitive();
        virtual glm::vec4 checkHit(Ray r){ return glm::vec4(0,0,0,0); };
        
        void setDiffuse(glm::vec3 d){ diffuse = d; };
        void setSpecular(glm::vec3 s){ specular = s; };
        void setShininess(float s){ shininess = s; };
        void setEmission(glm::vec3 e){ emission = e; };
        void setAmbient(glm::vec3 a){ ambient = a; };

        glm::vec3 getDiffuse(){ return diffuse; };
        glm::vec3 getSpecular(){ return specular; };
        float getShininess(){ return shininess; };
        glm::vec3 getEmission(){ return emission; };
        glm::vec3 getAmbient(){ return ambient; };
};