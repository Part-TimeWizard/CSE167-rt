#include <glm/glm.hpp>

#ifndef __RAY_H__
#define __RAY_H__

struct Ray {
public: 
    glm::vec3 ori;    // origin point of ray
    glm::vec3 dir;    // directional vector of ray
    
    Ray();
    Ray(glm::vec3 origin, glm::vec3 direction);
    ~Ray();
};

#endif
