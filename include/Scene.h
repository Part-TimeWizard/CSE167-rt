/**
 *  Scene.h
 * 
 * 
 */
#include "Primitive.h"
#include "Triangle.h"
#include "Sphere.h"
#include <vector>
#include <string>

#pragma once

class Scene {

    public:
        Scene();

        glm::vec2 imageSize;
        int maxDepth;
        glm::vec3 attenuation;
        glm::vec3 ambient;
        std::string outFileName;
        std::vector<Primitive> primList; // Used to iterate thru and checkHit of all primitives

        void pushTransform();
        void popTransform();

    private:
        enum class TransformType {Translate, Rotate, Scale};
        struct Transforms {
            TransformType transformType;
            glm::vec3 transformVector;
            float transformAngle;
        };

        std::vector<Scene::Transforms> TransformStack;

};