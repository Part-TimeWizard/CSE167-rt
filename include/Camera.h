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
	float aspect;		// aspect ratio 
	int h; 				// image size 
	int w; 

	Camera(); 
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 normal, float fov, int height, int width); 
	~Camera(); 

	void computeProjection(int width, int height); 
	Ray RayThruPixel(Camera camera, int i, int j); 
};

#endif 