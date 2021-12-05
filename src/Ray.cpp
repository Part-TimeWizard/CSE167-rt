#include "Ray.h"

/*
** Constructors
*/

Ray::Ray () {}
Ray::~Ray() {}

Ray::Ray (glm::vec3 origin, glm::vec3 direction) {
    r_ori = origin;
    r_dir = direction;
}

/*
** Methods
*/
glm::vec3 Ray::getOri() {
    return r_ori;
}

glm::vec3 Ray::getDir() {
    return r_dir; 
}
