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

bool Scene::isVisible(Ray ray) {
    for (Primitive* solid : objectStack) {
        if (solid == nullptr) {
            continue; 
        }
        glm::vec4 intPos = solid->checkHit(ray); 
        if (intPos[3] == 1) 
            return true; 
    }
    return false; 
}

glm::vec3 static Scene::findColor(RayHit* hray, vector<Light*> lights) {
  
    glm::vec3 finalColor; 

    // get material values for the first solid hit 
    if (hray->solid != nullptr) {
        glm::vec3 a = hray->solid->getAmbient(); 
        glm::vec3 e = hray->solid->getEmission();
        glm::vec3 d = hray->solid->getDiffuse(); 
        glm::vec3 s = hray->solid->getSpecular();
        float    sh = hray->solid->getShininess(); 
    }

    // iterate for each light 
    for (auto light : lights) {
        int vi; 
        Ray shadowRay;                                  // shadow ray for vi 
        glm::vec3 halfa;                                // half angle between viewdirection & light 
        glm::vec3 dsSum;                                // summation of diffuse & specular 
        glm::vec3 ldir = (light->pos) - (hray->pos);     // direction vector to light 

        // case for point light
        // attenuation is considered 
        if (typeid(light) == typeid(PointLight)) {

            // determine vi for point light 
            shadowRay = new Ray(hray->pos, glm::normalize(light->pos - hray->pos)); 
            if (scene.isVisible(shadowRay)) { vi = 1; } 
            else { vi = 0; }

            halfa = glm::normalize(ldir - hray->ray->dir);    // determine half angle for point light 

            dsSum += vi * light->colorAt(hray->pos) * (d * max(glm::dot(hray->normal, ldir), 0) + s * (max(glm::dot(hray->normal, halfa), 0))^sh); 
        }

        // case for directional light 
        else {

            // determine vi for directional light 
            shadowRay = new Ray(ray->pos, light->dir); 
            if (scene.isVisible(shadowRay)) { vi = 1; }
            else { vi = 0; }

            halfa = glm::normalize(ldir - hray->ray->dir); 
            dsSum += vi * light->color * (d * max(glm::dot(hray->normal, ldir), 0) + s * (max(glm::dot(hray->normal, halfa), 0))^sh);
        }
    }
    finalColor = a + e + dsSum;
}