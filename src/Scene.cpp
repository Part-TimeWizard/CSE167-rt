#include "Scene.h"

glm::vec3 zero(0.0f, 0.0f, 0.0f); // global variable to check no intersection 

Scene::Scene(int iWidth, int iHeight, int d, std::string o) {
    imageWidth = iWidth;
    imageHeight = iHeight;
    maxDepth = d;
    outFileName = o;
    attenuation = glm::vec3(1.0f,0.0f,0.0f);

    // TODO remember the better way to do this
    for( int i = 0; i < imageWidth*imageHeight*3; i++ ) {
        pixelData.push_back(static_cast<BYTE>(0));
        pixelData.push_back(static_cast<BYTE>(0));
        pixelData.push_back(static_cast<BYTE>(0));
    }
}

void Scene::setPixel(int x, int y, glm::vec3 color) {
    int convertedIdx = (y * imageWidth * 3) + x*3;
    pixelData[convertedIdx] = color[0]*255;
    pixelData[convertedIdx + 1] = color[1]*255;
    pixelData[convertedIdx + 2] = color[2]*255;
}

void Scene::addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh) {
    Triangle* newTri = new Triangle(v1, v2, v3, a, sp, d, e, sh);
    objectStack.push_back(newTri);
    //std::cout<<"Triangle Created: "<<newTri<<"="<<objectStack[objectStack.size()-1]<<std::endl;
}

void Scene::addSphere(glm::vec3 p, float r, glm::mat4 t, glm::vec3 a, glm::vec3 sp, glm::vec3 d, glm::vec3 e, float sh) {
    Sphere* newSphere = new Sphere(p, r, t,  a, sp, d, e, sh);
    objectStack.push_back(newSphere);
}

void Scene::addLight(glm::vec3 v, glm::vec3 color, int type) {
    if (type == 0) { // Point
        PointLight* newLight = new PointLight(v, color, attenuation);
        lights.push_back(newLight);
        std::cout<<"Point Light Created"<<std::endl;
    } else { // Directional
        DirectionalLight* newLight = new DirectionalLight(v, color, attenuation);
        lights.push_back(newLight);
        std::cout<<"Directional Light Created"<<std::endl;
    }
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
            //std::cout<<"Hit"<<std::endl;
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

glm::vec3 Scene::findColor(RayHit hray) {
  
    glm::vec3 finalColor; 

    // get material values for the first solid hit 
    glm::vec3 a = hray.solid->getAmbient(); 
    glm::vec3 e = hray.solid->getEmission();
    glm::vec3 d = hray.solid->getDiffuse(); 
    glm::vec3 s = hray.solid->getSpecular();
    float sh = hray.solid->getShininess(); 
    glm::vec3 dsSum;                                // summation of diffuse & specular 


    // iterate for each light 
    for (auto light : lights) {
        float vi; 
        Ray shadowRay;                                  // shadow ray for vi 
        glm::vec3 halfa;                                // half angle between viewdirection & light 
        glm::vec3 ldir = (light->pos) - (hray.pos);     // direction vector to light 
        ldir = glm::normalize(ldir);
        float nlDot = glm::dot(hray.normal, ldir); 

        // case for point light
        // attenuation is considered 
        if (typeid(light) == typeid(PointLight)) {

            // determine vi for point light 
            shadowRay = Ray(hray.pos, glm::normalize(light->pos - hray.pos)); 
            if (isVisible(shadowRay)) { vi = 1.0f; } 
            else { vi = 0.0f; }

            halfa = glm::normalize(ldir - hray.ray.dir);    // determine half angle for point light 

            dsSum += vi * light->colorAt(hray.pos) * (d * std::max(glm::dot(hray.normal, ldir), 0.0f) + s * (std::powf(std::max(glm::dot(hray.normal, halfa), 0.0f),sh))); 
        }

        // case for directional light 
        else if (typeid(light) == typeid(DirectionalLight)) {

            // determine vi for directional light 
            shadowRay = Ray(hray.pos, light->dir); 
            if (isVisible(shadowRay)) { vi = 1.0f; }
            else { vi = 0.0f; }

            halfa = glm::normalize(ldir - hray.ray.dir); 
            dsSum += vi * light->color * (d * std::max(glm::dot(hray.normal, ldir), 0.0f) + s * (std::powf(std::max(glm::dot(hray.normal, halfa), 0.0f), sh)));
        }
    }
    //std::cout<<"a: "<<a[0]<<","<<a[1]<<","<<a[2]<<std::endl;
    //std::cout<<"e: "<<e[0]<<","<<e[1]<<","<<e[2]<<std::endl;
    //std::cout<<"dsSum: "<<dsSum[0]<<","<<dsSum[1]<<","<<dsSum[2]<<std::endl<<std::endl;
    finalColor = a + e + dsSum;
    return finalColor; 
}

void Scene::render() {
    std::cout<<"Beginning Render..."<<std::endl;
    for(int y = 0; y < imageHeight; y++) {
        for(int x = 0; x < imageWidth; x++) {
            Ray ray = camera->RayThruPixel(x, y); 
            
            RayHit intObj = raycast(ray); 
            // Can access intObj.ray to use for FindColor() 
            if(intObj.solid == nullptr) {
                //setPixel(x, y, glm::vec3(0,0,0));
                setPixel(x, y, glm::vec3(0,0,0));
            } else {
                //setPixel(x,y,glm::vec3(0,255,0));
                setPixel(x, y, findColor(intObj));
            }
        }
    }
}