#include "ParticleGenerator.h"
#include <iostream>

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, 
	GLuint amount, Camera* c, float s, float l, float a,int type)
	: shader(shader), texture(texture), amount(amount), scale(s), life(l), a_atten(a),bubbles("resources/Models/particles/Bublbles.obj")
{
	this->type = type;
	theCamera = c;
	this->init();
}

void ParticleGenerator::Update(GLfloat dt, Transform &object, GLuint newParticles,
	glm::vec3 offset)
{
	// Add new particles 
	for (GLuint i = 0; i < newParticles; ++i) {
		int unusedParticle = this->firstUnusedParticle();//找到第一个未使用的粒子位置
	//s	std::cout << unusedParticle <<"********"<< std::endl;
		if (unusedParticle == -1)break;//不需要处理
		this->respawnParticle(this->particles[unusedParticle], object, offset);
	}
	// Update all particles
	for (GLuint i = 0; i < this->amount; ++i)
	{
		Particle &p = this->particles[i];
		p.Life -= dt; // reduce life
		if (p.Life > 0.0f)
		{	// particle is alive, thus update
			GLfloat k = 1;//粘滞阻力系数
			glm::vec3 acce;
			if (type == 1) {
				acce = -p.Velocity*k*p.scale*p.scale + glm::vec3(0, 20, 0)*p.scale*p.scale*p.scale;//加速度=粘滞阻力+浮力
				p.scale = p.initialScale*1*pow(double(23 / (10 * (100.0 + p.Position.y*3))), 0.3333);//压强影响体积的方程，也就是说，气泡越靠近水面就越大
			}
			if (type == 2) {
				acce = -p.Velocity*k*p.scale*p.scale*(0.1f)*0.5f + glm::vec3(0, -15, 0);
				p.scale = 4*sqrt(p.Life/8);
			}
			if (type == 3) {
				acce = glm::vec3(0, 0, 0);
			}

			p.Velocity += acce * dt;//动力学方程
			p.Position += p.Velocity * dt;


		//	p.Color.a -= dt * a_atten;
		//	std::cout << "life" << p.Life << " " << p.Velocity.x << " " << p.Velocity.y << " " << p.Velocity.z << std::endl;
		}
	}
}

// Render all particles
void ParticleGenerator::Draw()
{

//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->shader.use();
//	this->texture.Bind();
//	glBindVertexArray(cubeVAO);
	for (std::vector<Particle>::iterator it = particles.begin();
		it != particles.end();
		++it) {
		if (it->Life > 0.0f) {

			glm::mat4 projection = glm::perspective(glm::radians(theCamera->Zoom), (float)800 / (float)600, 0.1f, 1000.0f);
			glm::mat4 view = theCamera->GetViewMatrix();
			shader.setMat4("projection", projection);
			shader.setMat4("view", view);
			glm::mat4 model = glm::mat4(1.0f);
			


	//		std::cout << "该粒子的寿命" << it->Life<<"粒子总数"<<particles.size() << std::endl;
		//	std::cout <<"该粒子的坐标"<< it->Position.x << " " << it->Position.y << " " << it->Position.z << std::endl;
		//	std::cout << "该粒子的速度" << it->Velocity.x << " " << it->Velocity.y << " " << it->Velocity.z << std::endl<<std::endl;
			model = glm::translate(model, it->Position);//传入粒子的位置
			model = glm::scale(model, glm::vec3(it->scale, it->scale, it->scale));




			shader.setMat4("model", model);
			if (type == 1 || type == 3) {
				shader.setVec4("myColor", glm::vec4(1,1,1,0.4));
			}
			if (type == 2) {
				shader.setVec4("myColor", glm::vec4(1, 0, 0,1));
			}

		//	glDrawArrays(GL_TRIANGLES, 0, 36);
			bubbles.Draw(shader);
		}
	}

//	glBindVertexArray(0);
//	glUseProgram(0);

//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init()
{
	// Set up mesh and attribute properties
/*	if (cubeVAO == 0)
	{
		float vertices[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
			// bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			// top face
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
		};
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		// fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// link vertex attributes
		glBindVertexArray(cubeVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	glBindTexture(GL_TEXTURE_2D, texture.ID);//绑定给粒子绑定贴图
	*/
	this->particles = std::vector<Particle>(this->amount, Particle());
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint ParticleGenerator::firstUnusedParticle()
{
	// First search from last used particle, this will usually return almost instantly
	for (GLuint i = 0; i < this->amount; ++i) {
		if (this->particles[i].Life <= 0.0f) {
		//	lastUsedParticle = i;
			return i;//这个粒子需要被更新
		}
	}

	return -1;//目前所有的粒子都在被使用
}

void ParticleGenerator::respawnParticle(Particle &particle, Transform &object,
	glm::vec3 offset)
{
	//随机产生一个粒子
	//-5到+5的随机数
	GLfloat random1 = ((rand() % 100) - 50) / 10.0f;
	GLfloat random2= ((rand() % 100) - 50) / 10.0f;
	GLfloat random3 = ((rand() % 100) - 50) / 10.0f;
	GLfloat random4 = ((rand() % 100) - 50) / 10.0f;
	GLfloat randomtime = ((rand() % 100) - 50) / 10.0f;
	//随机颜色
	GLfloat rColor1 = 0.5 + ((rand() % 100) / 100.0f);
	GLfloat rColor2 = -1.0 + ((rand() % 100) / 100.0f) * 2;
	GLfloat rColor3 = -1.0 + ((rand() % 100) / 100.0f) * 2;
//	particle.Position = object.Position + random + offset;
	if (type == 1) {
		particle.Life = life + randomtime;
		particle.Velocity = glm::vec3(random1 / 4, random2 / 4, random3 / 4);
		particle.Position = object.Position;
		particle.initialScale = 1 + random4 / 5;//使得初始的气泡大小错落不一
	}
	if (type == 2) {
		particle.Life = life + randomtime / 5;
		particle.Velocity = glm::vec3(random1*40, abs(random2 *40), random3 *40 )+object.Velocity;
		particle.Position = object.Position;
	}
	if (type == 3) {
		particle.Life = life+randomtime*3;
		particle.Velocity = glm::vec3(random1, random2, random3);
		particle.Position = glm::vec3(random1 * 200, random2 * 200, random3 * 200);
	}
}

void ParticleGenerator::Reset()
{
	for (auto &particle : this->particles) {
		particle.Life = 0.0f;
	}
}