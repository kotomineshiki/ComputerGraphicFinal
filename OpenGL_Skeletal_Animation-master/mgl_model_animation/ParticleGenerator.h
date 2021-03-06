#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <ctime>
#include"Texture2D.h"
#include"Transform.h"
#include "shader.h"
#include "camera.h"
#include"model.h"
#include<string>
struct Particle {
	glm::vec3 Position, Velocity;
	GLfloat scale;
	GLfloat initialScale;
	glm::vec4 Color;
	GLfloat Life;
	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { scale = 1; }
};
class ParticleGenerator
{
public:
	Model bubbles;
	ParticleGenerator(Shader shader, Texture2D texture, GLuint amount, Camera* c,
		float scale = 20.0f, float life = 5.0f, float a = 2.5f,int type=1);
	// Update all particles
	void Update(GLfloat dt, Transform &object, GLuint newParticles,
		glm::vec3 offset = glm::vec3(0.0f, 0.0f,0.0f));
	// Render all particles
	void Draw();
	//粒子复位
	void Reset();
private:
	Camera* theCamera;
	std::vector<Particle> particles;//所有的粒子都在里面
	GLuint amount;
	float scale;
	Shader shader;
	Texture2D texture;
	GLuint VAO;

	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;

	GLfloat life;	//粒子最终寿命

	GLfloat a_atten;	//alpha衰减速度

	int type=1;//type1=气泡；type2=火山喷发；type3=浮游生物碎屑
	void init();
	// Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
	GLuint firstUnusedParticle();
	// Respawns particle
	void respawnParticle(Particle &particle, Transform &object,
		glm::vec3 offset = glm::vec3(0.0f, 0.0f,0.0f));
};

