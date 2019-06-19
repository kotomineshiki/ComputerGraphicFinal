#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include <iostream>

using namespace std;

class GameObject {
public:
	//whether the object can move
	bool isStuck;
	//the center of the object, we think the object as a circle when we detect collision
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotateAxis;
	//speed
	glm::vec3 velocity;
	//the size of the object
	float radius;
	//Angle: the forward direction
	float radiansForward;
	//Angle: the back direction
	float radiansBack;
	//indicate direction
	int For_Back;
	glm::mat4 modelMatrix;
	//whether two objects are collided
	bool isCollided;
	//when two objects have collided, the lock is set to true to avoid detecting multiple collision; when they are far away from each other. the lock will be set to false.
	bool lock;
    
    static Camera* camera_ptr;

	GameObject() {}
	GameObject(bool Stuck, glm::vec3 Pos, glm::vec3 Scale, glm::vec3 RotateAxis, 
		glm::vec3 Velocity, float Radius, float RadiansForward, float RadiansBack) : isStuck(Stuck), 
		position(Pos), scale(Scale), rotateAxis(RotateAxis), velocity(Velocity), radius(Radius), 
		radiansForward(RadiansForward), radiansBack(RadiansBack), For_Back(1), isCollided(false), lock(false) {}
	
	void setObject(bool Stuck, glm::vec3 Pos, glm::vec3 Scale, glm::vec3 RotateAxis,
		glm::vec3 Velocity, float Radius, float RadiansForward, float RadiansBack) {
		this->isStuck = Stuck;
		this->position = Pos;
		this->scale = Scale;
		this->rotateAxis = RotateAxis;
		this->velocity = Velocity;
		this->radius = Radius;
		this->radiansForward = RadiansForward;
		this->radiansBack = RadiansBack;
		this->For_Back = 1;
		this->isCollided = false;
		this->lock = false;
	}

	bool static DetectCollision(GameObject &one, GameObject &two) {
		glm::vec3 difference = one.position - two.position;
		if (glm::length(difference) < one.radius + two.radius) {
			return true;
		}
		return false;
	}
	glm::mat4 Move() {
		//if the object can move
		if (!this->isStuck) {
			//if the object has collided with other object or reach the boundary of the map
			if ((isCollided && !lock) || this->position.x - this->radius <= -500.0f || this->position.x + this->radius >= 500.0f || this->position.z - this->radius <= -500.0f || this->position.z + this->radius >= 500.0f)
			{
				this->velocity = -this->velocity;
				this->For_Back = -this->For_Back;
				isCollided = false;
				//lock is set to true to avoid detecting multiple collision.
				lock = true;
			}
			this->position += this->velocity;
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
		//first collision
		if (lock == false) {
			isCollided = true;
		}
	}
	void CollidedOut() {
		//far away from another object
		if (lock == true) {
			lock = false;
		}
	}
    
    static void CameraCollision(GameObject& obj) {
        glm::vec3 difference = camera_ptr->Position - obj.position;
        float collisionDepth = obj.radius - glm::length(difference);
        if (collisionDepth > 0) {
            camera_ptr->Position += collisionDepth * difference;
        }
    }
    template <typename ... Args>
    static void CameraCollision(GameObject& obj, Args ... args) {
        glm::vec3 difference = camera_ptr->Position - obj.position;
        float collisionDepth = obj.radius - glm::length(difference);
        if (collisionDepth > 0) {
            camera_ptr->Position += collisionDepth * difference;
        }
        CameraCollision(args...);
    }
};

#endif
