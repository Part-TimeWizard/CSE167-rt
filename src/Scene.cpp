/**
 *  Scene.cpp
 * 
 * 
 */
#include "Scene.h"
#include <iostream>

glm::vec3 zero(0.0f, 0.0f, 0.0f); // global variable to check no intersection 

Scene::Scene(int iWidth, int iHeight, int d, std::string o) {
    imageWidth = iWidth;
    imageHeight = iHeight;
    maxDepth = d;
    outFileName = o;

    // TODO remember the better way to do this
    for( int i = 0; i < imageWidth*imageHeight*3; i++ ) {
        pixelData.push_back(static_cast<BYTE>(0));
        pixelData.push_back(static_cast<BYTE>(0));
        pixelData.push_back(static_cast<BYTE>(0));
    }
}

void Scene::setPixel(int x, int y, glm::vec3 color) {
    int convertedIdx = (y * imageWidth * 3) + x*3;
    pixelData[convertedIdx] = color[0];
    pixelData[convertedIdx + 1] = color[1];
    pixelData[convertedIdx + 2] = color[2];
}

void Scene::addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh) {
    Triangle* newTri = new Triangle(v1, v2, v3, a, sp, d, e, sh);
    objectStack.push_back(newTri);
}

void Scene::addSphere(glm::vec3 p, float r, glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh) {
    Sphere* newSphere = new Sphere(p, r, a, sp, d, e, sh);
    objectStack.push_back(newSphere);
}

/**
 * @brief generates intersection object containing point of intersection
 *        and associated ray 
 * 
 * @param ray 
 * @return RayHit 
 */
RayHit Scene::raycast(Ray ray) {
    RayHit intersection = RayHit(ray, nullptr, glm::vec3(0.0f,0.0f,0.0f));
    bool firstHit = true; 

    // iterate through objectStack and check for first intersection 
    for (Primitive* solid : objectStack) {
        if (solid == nullptr) {
            continue; 
        }

        glm::vec4 intPos = solid->checkHit(ray); 

        float secDist = glm::distance(intersection.pos, ray.ori); 
        float intDist = glm::distance(glm::vec3(intPos[0],intPos[1],intPos[2]), ray.ori); 
        
        if (intPos[3] == 1 && (firstHit || secDist > intDist)) {
            std::cout<<"Hit"<<std::endl;
            intersection = RayHit(ray, solid, glm::vec3(intPos[0],intPos[1],intPos[2])); 
            firstHit = false; 
        }
    }
    return intersection; 
}