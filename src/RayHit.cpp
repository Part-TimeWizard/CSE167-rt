#include "RayHit.h"

Ray::RayHit (Ray ray, Primitive solid, glm::vec3 point) {
    ray = ray;
    solid = solid;
    h_pos = point;
    normal = glm::normalalize(point);
}

Ray RayHit::getRay() {
    return ray;
}

Primitive RayHit::getPrim() {
    return solid;
}

glm::vec3 RayHit::getPos() {
    return h_pos;
}

glm::vec3 RayHit::getNorm() {
    return normal;
}
