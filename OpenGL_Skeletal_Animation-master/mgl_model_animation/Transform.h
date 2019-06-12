#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
class Transform {
public:
	glm::vec3 Position;//当前位置
	glm::vec3 Velocity;//当前速度
	Transform() {
		Position = glm::vec3(0.0f, 0.0f, 0.0f);
		Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	}
};