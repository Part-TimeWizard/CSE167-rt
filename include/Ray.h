#include <glm/glm.hpp>

#ifndef __RAY_H__
#define __RAY_H__

struct Ray {
public: 
    glm::vec3 r_ori;    // origin point of ray
    glm::vec3 r_dir;    // directional vector of ray
    
    glm::vec3 getOri();
    glm::vec3 getDir();

    Ray();
    Ray(glm::vec3 origin, glm::vec3 direction);
    ~Ray();
};

#endif
