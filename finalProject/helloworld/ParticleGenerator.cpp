#include "ParticleGenerator.h"
#include <iostream>

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture,
	GLuint amount, float s, float l, float a)
	: shader(shader), texture(texture), amount(amount), scale(s), life(l), a_atten(a)
{
	this->init();
}

void ParticleGenerator::Update(GLfloat dt, Transform &object, GLuint newParticles,
	glm::vec3 offset, int way, int type)
{
	// Add new particles 
	for (GLuint i = 0; i < newParticles; ++i) {
		int unusedParticle = this->firstUnusedParticle();//�ҵ���һ��δʹ�õ�����λ��
		this->respawnParticle(this->particles[unusedParticle], object, offset, way, type);
	}
	// Update all particles
	for (GLuint i = 0; i < this->amount; ++i)
	{
		Particle &p = this->particles[i];
		p.Life -= dt; // reduce life
		if (p.Life > 0.0f)
		{	// particle is alive, thus update
			p.Position -= p.Velocity * dt;
			p.Color.a -= dt * a_atten;
		}
	}
}

// Render all particles
void ParticleGenerator::Draw()
{
	std::cout << "2321"<<std::endl;
	// Use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//this->shader.Use();
	this->shader.use();
	this->texture.Bind();
	glBindVertexArray(this->VAO);
	for (std::vector<Particle>::iterator it = particles.begin();
		it != particles.end();
		++it) {
		if (it->Life > 0.0f) {
		//	this->shader.SetVector2f("offset", it->Position);
		//	this->shader.SetVector4f("color", it->Color);
		//	this->shader.SetFloat("scale", this->scale);
			this->shader.setVec2("offset", it->Position);
			this->shader.setVec4("color", it->Color);
			this->shader.setFloat("scale", this->scale);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	glBindVertexArray(0);
	glUseProgram(0);
	// Don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init()
{
	// Set up mesh and attribute properties
	GLuint VBO;
	GLfloat particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// Set mesh attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create this->amount default particle instances
	this->particles = std::vector<Particle>(this->amount, Particle());
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
GLuint ParticleGenerator::firstUnusedParticle()
{
	// First search from last used particle, this will usually return almost instantly
	for (GLuint i = lastUsedParticle; i < this->amount; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Otherwise, do a linear search����Last֮��δ�ҵ��б�ɱ��������
	for (GLuint i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// All particles are taken, override the first one
	//(note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::respawnParticle(Particle &particle, Transform &object,
	glm::vec3 offset, int way, int type)
{
	//�������һ������
	//-5��+5�������
	GLfloat random = ((rand() % 100) - 50) / 10.0f;
	//�����ɫ
	GLfloat rColor1 = 0.5 + ((rand() % 100) / 100.0f);
	GLfloat rColor2 = -1.0 + ((rand() % 100) / 100.0f) * 2;
	GLfloat rColor3 = -1.0 + ((rand() % 100) / 100.0f) * 2;
	particle.Position = object.Position + random + offset;
	particle.Life = life;
	if (way == 1) {
		particle.Velocity = object.Velocity * 0.2f;
		particle.Color = glm::vec4(rColor1, (rColor2 + 1.0f) / 2.0f*0.6f, (rColor3 + 1.0f) / 2.0f*0.6f, 1.0f);
	}
	else if (way == 2) {
		glm::vec3 dir;
		dir.x = cos(180.0f*rColor2);
		dir.y = sin(180.0f*rColor2);
		particle.Velocity = glm::length(object.Velocity) * 0.4f * dir;
		particle.Color = glm::vec4(rColor1, (rColor2 + 1.0f) / 2.0f*0.6f, (rColor3 + 1.0f) / 2.0f*0.6f, 1.0f);
	}
	else if (way == 3) {
		glm::vec3 dir;
		int whichone = rand() % 2;
		switch (type) {
		case 0://ͭǮ��
			if (whichone == 0) {
				dir.x = pow(cos(180.0f*rColor2), 3);
				dir.y = pow(sin(180.0f*rColor2), 3);
			}
			else {
				dir.x = cos(180.0f*rColor2);
				dir.y = sin(180.0f*rColor2);
			}
			break;
		case 1://����
			dir.y = 2 * cos(180.0f*rColor2) - cos(2 * 180.0f*rColor2);
			dir.x = 2 * sin(180.0f*rColor2) - sin(2 * 180.0f*rColor2);
			break;
		case 2://��Ҷ����
			dir.x = sin(3 * 180.0f*rColor2)*cos(180.0f*rColor2);
			dir.y = sin(3 * 180.0f*rColor2)*sin(180.0f*rColor2);
			break;
		}
		GLfloat len = glm::length(object.Velocity);
		particle.Velocity = len * 0.4f * dir;
		particle.Color = glm::vec4(rColor1, (rColor2 + 1.0f) / 2.0f*0.8f, (rColor3 + 1.0f) / 2.0f*0.3f, 1.0f);
	}
}

void ParticleGenerator::Reset()
{
	for (auto &particle : this->particles) {
		particle.Life = 0.0f;
	}
}