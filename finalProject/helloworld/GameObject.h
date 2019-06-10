#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>

using namespace std;

class GameObject {
public:
	bool isStuck;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotateAxis;
	glm::vec3 velocity;
	float radius;
	float radiansForward;
	float radiansBack;
	int For_Back;
	glm::mat4 modelMatrix;
	bool isCollided;
	bool block;

	GameObject(bool Stuck, glm::vec3 Pos, glm::vec3 Scale, glm::vec3 RotateAxis, glm::vec3 Velocity, float Radius, float RadiansForward, float RadiansBack) : isStuck(Stuck), position(Pos), scale(Scale), rotateAxis(RotateAxis), velocity(Velocity), radius(Radius), radiansForward(RadiansForward), radiansBack(RadiansBack), For_Back(1), isCollided(false), block(false) {}
	bool static DetectCollision(GameObject &one, GameObject &two) {
		glm::vec3 difference = one.position - two.position;
		if (glm::length(difference) < one.radius + two.radius) {
			return true;
		}
		return false;
	}
	glm::mat4 Move() {
		if (!this->isStuck) {
			
			if ((isCollided&&!block) || this->position.x <= -100.0f || this->position.x >= 100.0f || this->position.z <= -100.0f || this->position.z >= 100.0f)
			{
				this->velocity = -this->velocity;
				this->For_Back = -this->For_Back;
				isCollided = false;
				block = true;
			}
			this->position += this->velocity;
			std::cout << this->For_Back << std::endl;
			modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, this->position);
			modelMatrix = glm::scale(modelMatrix, this->scale);
			if (this->For_Back == 1) {
				modelMatrix = glm::rotate(modelMatrix, glm::radians(this->radiansForward), this->rotateAxis);
			}
			else {
				modelMatrix = glm::rotate(modelMatrix, glm::radians(this->radiansBack), this->rotateAxis);
			}
			return modelMatrix;
		}
	}
	void CollidedIn() {
		if (block == false) {
			isCollided = true;
		}
		std::cout << "in" << std::endl;
	}
	void CollidedOut() {
		if (block == true) {
			block = false;
		}
	}
};

#endif