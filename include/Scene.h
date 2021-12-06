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
        Scene(int imageWidth, int imageHeight, int d = 5, std::string o = "outputImage.png");

        //glm::vec2 imageSize;
        int imageWidth;
        int imageHeight;
        std::vector<BYTE> pixelData;
        int maxDepth;
        glm::vec3 attenuation; 
        glm::vec3 ambient; // TODO Set per object, not globally
        std::string outFileName;
        std::vector<Primitive> primList; // Used to iterate thru and checkHit of all primitives

        void pushTransform();
        void popTransform();
        void setDepth(int d){maxDepth = d;};
        void setName(std::string n){outFileName = n;};
        void setPixel(int x, int y, glm::vec3 color);


    private:
        enum class TransformType {Translate, Rotate, Scale};
        struct Transforms {
            TransformType transformType;
            glm::vec3 transformVector;
            float transformAngle;
        };

        std::vector<Scene::Transforms> TransformStack;

};