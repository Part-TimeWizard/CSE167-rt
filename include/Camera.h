#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "Ray.h" 

#ifndef __CAMERA_H__
#define __CAMERA_H__ 

class Camera {
public: 
	glm::vec3 eye;		// position of camera
	glm::vec3 target;	// position camera is looking at
	glm::vec3 up;		// up vector 
	float fovy;			// input fov 
	float fovx;			// fov dependent on image size
	int h; 				// image size 
	int w; 

	glm::vec3 p_a; 		// alignment vector of projection (W vector) 
	glm::vec3 p_u;		// U vector of projection 
	glm::vec3 p_v; 		// V vector of projection 
	glm::vec3 p_c;		// center position of projection 

	Camera(); 
	Camera(const glm::vec3 position, const glm::vec3 direction, const glm::vec3 normal, const float fov, const int height, const int width); 
	~Camera(); 

	void computeProjection(); 
	Ray RayThruPixel(Camera camera, int i, int j); 
};

#endif 