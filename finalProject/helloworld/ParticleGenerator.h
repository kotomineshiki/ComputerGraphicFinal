#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <ctime>
#include <learnopengl/shader_m.h>
#include"Texture2D.h"
#include"Transform.h"
struct Particle {
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;
	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};
class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture2D texture, GLuint amount,
		float scale = 20.0f, float life = 1.0f, float a = 2.5f);
	// Update all particles
	void Update(GLfloat dt, Transform &object, GLuint newParticles,
		glm::vec3 offset = glm::vec3(0.0f, 0.0f,0.0f), int way = 1, int type = 0);
	// Render all particles
	void Draw();
	//���Ӹ�λ
	void Reset();
private:
	// State
	std::vector<Particle> particles;
	GLuint amount;
	float scale;
	// Render state
	Shader shader;
	Texture2D texture;
	GLuint VAO;
	//������������
	GLfloat life;
	//alpha˥���ٶ�
	GLfloat a_atten;
	// Initializes buffer and vertex attributes
	void init();
	// Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
	GLuint firstUnusedParticle();
	// Respawns particle
	void respawnParticle(Particle &particle, Transform &object,
		glm::vec3 offset = glm::vec3(0.0f, 0.0f,0.0f), int way = 1, int type = 0);
};

