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

	// Assign appropriate aspect ratio 
	fovy = glm::tan(fov / 2); 
	fovx = (w / h) * glm::tan(fov / 2); 
}

/**
 * @brief computes projection screen 
 * 
 */
void Camera::computeProjection() { 
	// 1) Compute vector from camera position to target position 
	p_a = target - eye; 
	p_a = glm::normalize(p_a); 

	// 2) Compute U and V vectors
	p_u = glm::cross(p_a, up); 
	p_u = glm::normalize(p_u); 
	p_v = glm::cross(p_u, p_a); 
	p_v = glm::normalize(p_v); 

	// 3) Compute position of the center point of the screen 
	p_c = eye + p_a; 

	// 4) Modify U and V vectors to match size and aspect ratio 
	p_u = p_u * fovx; 
	p_v = p_v * (fovx / fovy); 
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
	glm::vec3 rayDir = a * p_u + b * p_v - p_a; 
	rayDir = glm::normalize(rayDir); 

	// creating Ray 
	// might need to scale rayDir so Ray intersects with object 
	Ray outgoing(eye, rayDir); 

	return outgoing; 
}

