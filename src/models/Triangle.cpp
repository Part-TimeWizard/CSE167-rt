/**
 *  Triangle.cpp
 *  
 *  
 */
#include "Triangle.h"

glm::vec4 Triangle::checkHit(Ray r) {
    glm::vec3 p0 = r.ori;
    glm::vec3 d = r.dir;
    
    glm::vec4 a0 = glm::vec4(position[0],1.0f);
    glm::vec4 a1 = glm::vec4(position[1],1.0f);
    glm::vec4 a2 = glm::vec4(position[2],1.0f);
    glm::vec4 a3 = glm::vec4(-1.0f *d,0.0f);
    glm::mat4 a;
    a[0] = a0;
    a[1] = a1;
    a[2] = a2;
    a[3] = a3;
    glm::mat4 aInv = glm::inverse(a);
    glm::vec4 b = glm::vec4(p0, 1.0f);

    glm::vec4 lambdaVec = aInv * b;

    glm::vec3 q = lambdaVec[0]*position[0] + lambdaVec[1]*position[1] + lambdaVec[2]*position[2];

    if(lambdaVec[0] >= 0 && lambdaVec[1] >= 0 && lambdaVec[2] >= 0 && lambdaVec[3] >= 0) {
        return glm::vec4(q,1); // 1 means intersect
    } else {
        return glm::vec4(q,0); // 0 means no intersect
    }
}