/**
 *  Scene.h
 * 
 * 
 */
#define GLM_FORCE_RADIANS
#include "Primitive.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Ray.h"
#include "RayHit.h" 
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <stack>
#include <FreeImage.h>

#pragma once

class Scene {

    public:
        Scene(int iWidth, int iHeight, int d = 5, std::string o = "outputImage.png");

        //glm::vec2 imageSize;
        int imageWidth;
        int imageHeight;
        std::vector<BYTE> pixelData;
        int maxDepth;
        glm::vec3 attenuation; 
        std::string outFileName;
        std::vector<Primitive*> objectStack; // Used to iterate thru and checkHit of all primitives
        std::stack<glm::mat4> transformStack;
        Camera* camera;

        void addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh);
        void addSphere(glm::vec3 p, float r, glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh);
        void setDepth(int d){maxDepth = d;};
        void setName(std::string n){outFileName = n;};
        void setPixel(int x, int y, glm::vec3 color);
        RayHit raycast(Ray ray); 

    private:
        /*
        enum class TransformType {Translate, Rotate, Scale};
        struct Transforms {
            TransformType transformType;
            glm::vec3 transformVector;
            float transformAngle;
        };
        */


};