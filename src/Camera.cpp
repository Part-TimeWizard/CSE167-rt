#include "Camera.h"

/*
** Constructors 
*/

Camera::Camera() {} 
Camera::~Camera() {} 

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 normal, float fov, int height, int width) {
	eye = position;
	target = direction;
	up = normal; 
	fovy = fov;
	// fovx = 2 * arctan( tan (fovy/2) * (w/h) )
	fovx = 2 * glm::atan(glm::tan(fovy / 2) * (width / height)); 
	aspect = 1.0f;	// world aspect ratio always 1 
	h = height; 
	w = width; 
}

/**
 * @brief computes projection screen 
 * 
 * @param width	width of image 
 * @param height height of image 
 */
void Camera::computeProjection(int width, int height) { 
	// must complete
}

/**
 * @brief generates a ray originated from camera position,
 * 		  through center of (i, j) pixel into world 
 * 
 * @param camera camera position 
 * @param i 	 width coordinate 
 * @param j 	 height coordinate 
 * @return Ray 	 ray through (i, j) pixel from camera 
 */
Ray Camera::RayThruPixel(Camera camera, int i, int j) {

	// variables for finding center of pixel 
	// when screen ranges (-1,1) to (1,1) 
	float a = 2 * ((i + 0.5) / camera.w) - 1; 
	float b = 1 - 2 * ((j + 0.5) / camera.h); 
	glm::vec3 cpix(a, b, -1); 

	// creating new Ray 
	Ray outgoing; 
	outgoing.ori = camera.eye; // origin is camera 
	outgoing.dir = cpix; 
	
	return outgoing; 
}

