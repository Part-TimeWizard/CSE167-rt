#include "Camera.h"

/*
** Constructors 
*/

Camera::Camera() {} 
Camera::~Camera() {} 

Camera::Camera(glm::vec3 position, glm::vec3 direction, float fov, float width) {
	c_pos = position;
	c_dir = direction;
	c_up = glm::normalize(direction);
	fovy = fov;
	fovx = width;
	aspr = 1.0f;	// world aspect ratio always 1 
}

/*
** Methods
*/

void Camera::computeProjection(int width, int height) { 
	// must complete
}

glm::vec3 Camera::getPos() {
	return c_pos; 
}

glm::vec3 Camera::getDir() {
	return c_dir; 
 }