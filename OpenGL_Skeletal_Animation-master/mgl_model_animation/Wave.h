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
				y += 0.1* amplitudes[i][j] * cos(waveNums[i] * (x*cos(thetas[j]) + z * sin(thetas[j])) - omegas[i] * time);
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
		model = glm::translate(model, glm::vec3(1000.0f, 300, -400.0f));
		model = glm::scale(model, glm::vec3(80.0f, 120.0f, 95.0f));
		shader.setMat4("model", model);
		currentlandscape.Draw(shader,true);//绘制当前地图,而且要使用wave特有的绘制方法
	//	glDrawElements(GL_TRIANGLES, 81*6, GL_UNSIGNED_INT, 0);
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glDrawArrays(GL_TRIANGLES, 0, 36);

	//	glBindVertexArray(0);
	//	glUseProgram(0);
	}
};