#include "Camera.h"

/*
** Constructors 
*/

Camera::Camera() {} 
Camera::~Camera() {} 

Camera::Camera(const glm::vec3 position, const glm::vec3 direction, 
const glm::vec3 normal, float fov, int height, int width) {
	// Assign basic attributes 
	eye = position;
	target = direction;
	up = normal; 
	h = height; 
	w = width; 
	aspr = w / h; 

	// Assign appropriate world aspect ratio 
	fovy = glm::tan(fov / 2); 
	fovx = aspr * glm::tan(fov / 2); 

	computeProjection();
}

/**
 * @brief computes projection screen 
 * 
 */
void Camera::computeProjection() { 
	// 1) Compute vector from camera position to target position 
	c_w = eye - target; 
	c_w = glm::normalize(c_w); 

	// 2) Compute U and V vectors
	c_u = glm::cross(up, c_w); 
	c_u = glm::normalize(c_u); 
	c_v = glm::cross(c_w, c_u); 

	// 3) Compute position of the center point of the screen 
	p_c = eye - c_w; 

	// 4) Update projection's U and V vectors to match size and aspect ratio 
	p_u = c_u * fovx; 
	p_v = c_v * fovy; 
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
Ray Camera::RayThruPixel(int i, int j) {

	// variables for finding center of pixel when screen ranges (-1,1) to (1,1) 
	float a = 2 * ((i + 0.5) / w) - 1; 
	float b = 1 - 2 * ((j + 0.5) / h); 

	// finding directional vector of Ray 
	// @ref 		RayTracing class slides 
	// @formula 	d = (aU + bV - W) / |aU + bV - W|  
	glm::vec3 rayDir = a * c_u + b * c_v - c_w; 
	rayDir = glm::normalize(rayDir); 

	// creating Ray 
	// might need to scale rayDir so Ray intersects with object 
	Ray outgoing(eye, rayDir); 

	return outgoing; 
}

