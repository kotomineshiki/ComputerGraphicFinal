#pragma once
//#include <glad/glad.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <learnopengl/filesystem.h>

#include"camera.h"
#include"shader.h"

#include"ParticleGenerator.h"
#include "GameObject.h"
#include <time.h>
#include <stdlib.h>
#include"model.h"


using namespace std;




class Wave {
public:
	Model landscape;
	Model currentlandscape;
	Wave() :landscape("resources/Models/landscape/untitled.obj"), currentlandscape("resources/Models/landscape/untitled.obj") {

	}
	/*	float vertices[800];	//水面顶点数组
		uint indices[81*6];	//水面索引数组
		GLuint VAO;
	//	Texture texture;
		unsigned int waveVAO = 0;
		unsigned int waveVBO = 0;
		unsigned int waveEBO = 0;
		Wave() {
			Init();//初始化波浪
		}
		void Init() {//初始化波形状
				// Set up mesh and attribute properties
			if (waveVAO == 0)
			{
				for (int i = 0; i < 10; ++i) {//这是一个平面
					for (int j = 0; j < 10; ++j) {
						vertices[(i * 10 + j) * 8 + 0] = i-5;//x
						vertices[(i * 10 + j) * 8 + 1] = 0;//y
						vertices[(i * 10 + j) * 8 + 2] = j - 5;//z

					//	vertices[(i * 10 + j) * 8 + 3] = 0;//x
					//	vertices[(i * 10 + j) * 8 + 4] = 0;//y
					//	vertices[(i * 10 + j) * 8 + 5] = 0;//z
					}
				}
				int indices_end = 0;
				for (int i = 0; i < 9; ++i) { //i,j   i,j+1
											  //i+1,j i+1,j+1
					for (int j = 0; j < 9; ++j) {
						indices[indices_end++] = 10 * i + j;
						indices[indices_end++] = 10 * i + j + 1;
						indices[indices_end++] = 10 * (i + 1) + j;

						indices[indices_end++] = 10 * i + j + 1;
						indices[indices_end++] = 10 * (i + 1) + j;
						indices[indices_end++] = 10 * (i + 1) + j + 1;
					}
				}
				glGenVertexArrays(1, &waveVAO);
				glGenBuffers(1, &waveVBO);
				glGenBuffers(1, &waveEBO);
				// fill buffer
				glBindBuffer(GL_ARRAY_BUFFER, waveVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, waveEBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
				// link vertex attributes
				glBindVertexArray(waveVAO);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
			}
		//	this->particles = std::vector<Particle>(this->amount, Particle());
	//		glBindTexture(GL_TEXTURE_2D, texture.ID);//绑定给粒子绑定贴图
		}*/
	void Update() {//根据时间来变换波函数的节点
		//std::cout << currentlandscape.meshes.size() <<"____________________"<< endl;
		float time = glfwGetTime();
		for (int i = 0; i < currentlandscape.meshes[0].vertices.size(); ++i) {//每14个一周期
			glm::vec3 calculatePosition = landscape.meshes[0].vertices[i].Position;

			calculatePosition = Gerstner(calculatePosition, time);
			//calculatePosition.y += 0.3 * cos(1 * time - calculatePosition.x) + 0.15 * cos(2 * time - 2 * calculatePosition.x) + 0.1 * cos(4 * time - 3 * calculatePosition.x);//波动方程
			currentlandscape.meshes[0].vertices[i].Position = calculatePosition;
		}//这个是mesh数据
	//	std::cout << currentlandscape.meshes[0].vertices[0].Position.x << currentlandscape.meshes[0].vertices[0].Position.y << currentlandscape.meshes[0].vertices[0].Position.z << std::endl;
	}
	glm::vec3 Gerstner(glm::vec3 input,float time) {
		const int n = 3;  // 频率划分个数
		const int m = 2; // 方向的划分个数
		double thetas[m] = { 0.38,1.42 };  // 传播方向
		double amplitudes[n][m] = {  //波幅
			0.2,0.2,
			0.3,0.50,
			0.2,0.6,
		};
		double omegas[n] = { 3.27,3.31,3.42 };     //  角频率
		double waveNums[n] = { 1.091,1.118,1.1935 };  // 波数
		float x = input.x;
		float y = input.y;
		float z = input.z;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				x -= 0.2*cos(thetas[j])*amplitudes[i][j] * sin(waveNums[i] * (x*cos(thetas[j]) + z * sin(thetas[j])) - omegas[i] * time);
				y += 0.2* amplitudes[i][j] * cos(waveNums[i] * (x*cos(thetas[j]) + z * sin(thetas[j])) - omegas[i] * time);
				z -= 0.2*sin(thetas[j])*amplitudes[i][j] * sin(waveNums[i] * (x*cos(thetas[j]) + z * sin(thetas[j])) - omegas[i] * time);
			}
		}     return glm::vec3 (x, y, z);
	}

	
	/*void Update() {

	}*/
	void DrawLandscape( Shader &shader) {
	//	glBindVertexArray(waveVAO);

	//	shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		shader.setMat4("model", model);
		currentlandscape.Draw(shader,true);//绘制当前地图,而且要使用wave特有的绘制方法
	//	glDrawElements(GL_TRIANGLES, 81*6, GL_UNSIGNED_INT, 0);
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glDrawArrays(GL_TRIANGLES, 0, 36);

	//	glBindVertexArray(0);
	//	glUseProgram(0);
	}
};