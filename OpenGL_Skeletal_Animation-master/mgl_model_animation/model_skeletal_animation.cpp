#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "util.h";
#include "SkinnedMesh.h"

#include <iostream>
#include <filesystem>
namespace fs = std::experimental::filesystem;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;

// timing
extern float deltaTime;
extern float lastFrame;

int model_skeletal_animation()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "glew error";
	}
	Shader ourShaderTest("1.model_loading.vs", "1.model_loading.fs");
	Model ourModelTest("resources/Models/nanosuit/nanosuit.obj"); 
	
	glm::mat4 modelTest(1.0f);
	modelTest = glm::scale(modelTest, glm::vec3(0.8f, 0.8f, 0.8f));
	modelTest = glm::translate(modelTest, glm::vec3(0.0f, 0.0f, 0.0f));

	Shader ourShader("skinning.vs", "skinning2");

	SkinnedMesh ourModel;
	
	ourModel.LoadMesh("resources/Models/running/model.dae");//人物跑步动画
	//ourModel.LoadMesh("resources/Models/test/HarpyCat/Model/1.fbx");//鸟人动画
	//ourModel.LoadMesh("resources/Models/test/chicken/1.fbx");小鸡动画
	//ourModel.LoadMesh("resources/Models/test/MeshSmith/Fantasy1/Lady Fairy/Mesh/Lady Fairy.fbx");//静态小精灵
	//ourModel.LoadMesh("resources/Models/bob_lamp_update/boblampclean.md5mesh");守卫,人脸是倒立的,该资源可以不用
	
	static const uint MAX_BONES = 100;
	float m_startTime = glfwGetTime();
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ourShaderTest.use();

		glm::mat4 projectionTest = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 viewTest = camera.GetViewMatrix();
		ourShaderTest.setMat4("projection", projectionTest);
		ourShaderTest.setMat4("view", viewTest);
		modelTest = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		ourShaderTest.setMat4("model", modelTest);
		ourModelTest.Draw(ourShaderTest);

		ourShader.use();
		GLuint m_boneLocation[MAX_BONES];
		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation); i++) {
			char Name[128];
			memset(Name, 0, sizeof(Name));
			SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);

			m_boneLocation[i] = glGetUniformLocation(ourShader.ID, Name);
		}

		float RunningTime = (float)((double)glfwGetTime() - (double)m_startTime);// / 1000.0f;
		vector<Matrix4f> Transforms;

		ourModel.BoneTransform(RunningTime, Transforms);

		for (uint i = 0; i < Transforms.size(); i++) {
			//m_pEffect->SetBoneTransform(i, Transforms[i]);
			glUniformMatrix4fv(m_boneLocation[i], 1, GL_TRUE, (const GLfloat*)Transforms[i]);
		}



		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model(1.0f);
		//model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		ourShader.setMat4("model", model);


		ourModel.Render();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
