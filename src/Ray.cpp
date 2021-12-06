#include "Ray.h"

/*
** Constructors
*/

Ray::Ray () {}
Ray::~Ray() {}

Ray::Ray (glm::vec3 origin, glm::vec3 direction) {
    ori = origin;
    dir = direction;
}
