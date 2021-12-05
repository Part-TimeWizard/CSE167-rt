#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#ifndef __CAMERA_H__
#define __CAMERA_H__ 

class Camera {
public: 
	glm::vec3 c_pos;	// position of camera
	glm::vec3 c_dir;	// direction of camera
	glm::vec3 c_up;		// up vector 
	float fovy;			// fov 
	float fovx;			
	float aspr;			// aspect ratio 

	// default values 
	glm::vec3 c_posDef = glm::vec3(2.0f, 0.0f, 0.0f); 
	glm::vec3 c_dirDef = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 c_upDef = glm::vec3(0.0f, 1.0f, 0.0f);
	float fovy_def = 100.0f; 
	float aspr_def = 1.0f;		// always used 

	Camera(); 
	Camera(glm::vec3 position, glm::vec3 direction, float fov, float width); 
	~Camera(); 

	void computeProjection(float width, float height); 
	glm::vec3 getPos(); 
	glm::vec3 getDir(); 
};

#endif 