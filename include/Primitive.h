/**
 *  Primitive.h
 *  
 *  Parent class for Sphere and Triangle, contains material data and virtual class to check for ray intersection.
 */
#include <glm/glm.hpp>
#pragma once

class Primitive {

    private:
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;
        glm::vec3 emission;
        glm::vec3 ambient;

    public:
        virtual void checkHit(glm::vec3);
        virtual void transform(glm::vec3); // Used to apply transformations to the Primitive, applied in reverse to popTransforms

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