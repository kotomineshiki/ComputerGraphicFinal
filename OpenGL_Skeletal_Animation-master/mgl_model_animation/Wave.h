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
#include"model.h"
#include"ParticleGenerator.h"
#include "GameObject.h"
#include <time.h>
#include <stdlib.h>
class Wave {
public:
	Model landscape;
	Model currentlandscape;
	Wave():landscape("resources/Models/landscape/Ocean.obj"), currentlandscape("resources/Models/landscape/Ocean.obj") {

	}
	void Init() {//初始化波形状

	}
	void Update() {//根据时间来变换波函数的节点
		std::cout << currentlandscape.meshes.size() <<"____________________"<< endl;
		float time = glfwGetTime();
		for (int i = 0; i < currentlandscape.meshes[0].vertices.size(); ++i) {//每14个一周期
			glm::vec3 calculatePosition = landscape.meshes[0].vertices[i].Position;
			
			calculatePosition.z += 10 * cos(1 * time - calculatePosition.x);//波动方程
			currentlandscape.meshes[0].vertices[i].Position=calculatePosition;
		}//这个是mesh数据
		std::cout << currentlandscape.meshes[0].vertices[0].Position.x<< currentlandscape.meshes[0].vertices[0].Position.y<< currentlandscape.meshes[0].vertices[0].Position.z << std::endl;
	}
	void DrawLandscape(const Shader &shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		shader.setMat4("model", model);
		currentlandscape.Draw(shader);//绘制当前地图
	}
};