/**
 *  Scene.cpp
 * 
 * 
 */
#include "Scene.h"

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

void Scene::pushTransform() {

}

void Scene::popTransform() {

}

void Scene::addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
    Triangle* newTri = new Triangle(v1, v2, v3);
    objectStack.push_back(newTri);
}

void Scene::addSphere(glm::vec3 p, float r) {
    Sphere* newSphere = new Sphere(p, r);
    objectStack.push_back(newSphere);
}