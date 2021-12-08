/**
 *  Triangle.cpp
 *  
 *  
 */
#include "Triangle.h"

void Triangle::transform(glm::vec3) {
    return;
}

glm::vec3 Triangle::checkHit(glm::vec3 p0, glm::vec3 d) {
    glm::vec4 a0 = glm::vec4(position[0],1.0f);
    glm::vec4 a1 = glm::vec4(position[1],1.0f);
    glm::vec4 a2 = glm::vec4(position[2],1.0f);
    glm::vec4 a3 = glm::vec4(d,0.0f);
    a3 = -1.0f * a3;
    glm::mat4 a;
    a[0] = a0;
    a[1] = a1;
    a[2] = a2;
    a[3] = a3;
    glm::mat4 aInv = glm::inverse(a);
    glm::vec4 b = glm::vec4(p0, 1.0f);

    glm::vec4 lambdaVec = aInv * b;

    if(lambdaVec[0] >= 0 && lambdaVec[1] >= 0 && lambdaVec[2] >= 0 && lambdaVec[3] >= 0) {
        return getAmbient();
    } else {
        return glm::vec3(0,0,0);
    }
}