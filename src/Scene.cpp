/**
 *  Scene.cpp
 * 
 * 
 */
#include "Scene.h"

Scene::Scene(int imageWidth, int imageHeight, int d = 5, std::string o = "outputImage.png") {
    pixelData = std::vector<BYTE> a(imageWidth*imageHeight*3, 0);
}

void Scene::setPixel(int x, int y, glm::vec3 color) {
    int convertedIdx = (y * imageWidth * 3) + x*3;
    pixelData[convertedIdx] = color[0];
    pixelData[convertedIdx + 1] = color[1];
    pixelData[convertedIdx + 2] = color[2];
}