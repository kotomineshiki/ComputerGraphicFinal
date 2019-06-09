//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <learnopengl/filesystem.h>
//#include <learnopengl/shader_m.h>
//#include <learnopengl/camera.h>
//#include <learnopengl/model.h>
//
//#include <iostream>
//
//#include  <stdlib.h>    
//#include  <time.h>
//
//#include"SceneManager.h"
//#include"Skybox.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 100.0f, 1000.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	// ---------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile shaders
//	// -------------------------
//	Shader ourShader("1.model_loading.vs", "1.model_loading.fs");
//
//	// load models
//	// -----------
//	////Model rose(FileSystem::getPath("resources/objects/rose/rose.obj"));
//	//Model palm(FileSystem::getPath("resources/objects/palm/Palm_01.obj"));
//	////Model castle(FileSystem::getPath("resources/objects/castle/eastern ancient casttle.obj"));
//	Model city(FileSystem::getPath("resources/objects/city/Organodron City.obj"));
//
//	//Model landscape(FileSystem::getPath("resources/objects/landscape/Ocean.obj"));
//	//Model fish(FileSystem::getPath("resources/objects/fish/fish.obj"));
//	//Model fish2(FileSystem::getPath("resources/objects/fish2/13009_Coral_Beauty_Angelfish_v1_l3.obj"));
//	//Model fish3(FileSystem::getPath("resources/objects/fish3/12265_Fish_v1_L2.obj"));
//	//Model fish4(FileSystem::getPath("resources/objects/fish4/13013_Red_Head_Solon_Fairy_Wrasse_v1_l3.obj"));
//	////Model frog(FileSystem::getPath("resources/objects/frog/20436_Frog_v1 textured.obj"));
//	//Model whale(FileSystem::getPath("resources/objects/whale/10054_Whale_v2_L3.obj"));
//	//Model coralReef(FileSystem::getPath("resources/objects/coralReef/source/model.obj"));
//	//Model coralReef2(FileSystem::getPath("resources/objects/coralReef2/source/model.obj"));
//	//Model coralReef3(FileSystem::getPath("resources/objects/coralReef3/source/model.obj"));
//	//Model seaDragon(FileSystem::getPath("resources/objects/seaDragon/source/model.obj"));
//	//Model turtle(FileSystem::getPath("resources/objects/turtle/model.obj"));
//
//
//	// draw in wireframe
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	// render loop
//	// -----------
//
//	srand((unsigned)time(NULL));
//	float randomCoorX[50], randomCoorY[50], randomCoorZ[50];
//	for (int i = 0; i < 50; i++) {
//		randomCoorX[i] = rand() / double(RAND_MAX)*100.0f;
//		randomCoorY[i] = rand() / double(RAND_MAX)*100.0f;
//		randomCoorZ[i] = rand() / double(RAND_MAX)*100.0f;
//	}
//
//	SceneManager myScene(&camera);//这个是场景管理器
//
//	myScene.InitParticle();//初始化粒子
//
//	Skybox skybox; //天空盒
//
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		// --------------------
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//
//		// render
//		// ------
//		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// don't forget to enable shader before setting uniforms
//		ourShader.use();
//
//		// view/projection transformations
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 3000.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		ourShader.setMat4("projection", projection);
//		ourShader.setMat4("view", view);
//
//		// render the loaded model
//		/*glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(500.0f, 500.0f, 500.0f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		landscape.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -10.0f, 1000.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		city.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(500.0f, -20.0f, 500.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		coralReef.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(400.0f, -20.0f, -300.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		coralReef2.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(-600.0f, -130.0f, 650.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(-120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		coralReef3.Draw(ourShader);
//		float x[3] = { 570.0f, 450.0f, -650.0f }, z[3] = { 480.0f, -250.0f, 600.0f };
//		for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 50; j++) {
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(x[i] + randomCoorX[j], -1.0f, z[i] + randomCoorZ[j])); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		palm.Draw(ourShader);
//		}
//		}
//
//		for (int i = 0; i < 50; i++) {
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(-300.0f + randomCoorX[i], 130.0f + randomCoorY[i], 550.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		fish.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(-100.0f + randomCoorX[i], 530.0f + randomCoorY[i], 250.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		fish.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(500.0f + randomCoorX[i], 30.0f + randomCoorY[i], -400.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		fish2.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(500.0f + randomCoorX[i], 250.0f + randomCoorY[i], 450.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		fish3.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(-500.0f + randomCoorX[i], 400.0f + randomCoorY[i], -450.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		fish4.Draw(ourShader);
//		}
//
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(-50.0f, 700.0f, 300.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		whale.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(450.0f, 50.0f, 500.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		turtle.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(380.0f, 80.0f, 400.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		ourShader.setMat4("model", model);
//		turtle.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(-100.0f, 100.0f, 600.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		seaDragon.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, 50.0f, 500.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		seaDragon.Draw(ourShader);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(-50.0f, 100.0f, 520.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		seaDragon.Draw(ourShader);*/
//
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
//
//
//		ourShader.setMat4("model", model);
//		ourShader.setInt("texture_diffuse1", 0);
//		glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("lightPos", lightPos);
//		ourShader.setVec3("viewPos", camera.Position);
//
//
//		city.Draw(ourShader);
//
//
//		Transform debugTransform;
//		myScene.temptation->Update(deltaTime, debugTransform, 8, glm::vec3(1.0f, 1.0f, 1.0f), 2);
//		//渲染场景中的所有模型
//		myScene.DrawElements();//只需要调用这个函数就可以画出所有元素
//		
//		skybox.drawSkybox(projection, view);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime*30.0f);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime*30.0f);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime*30.0f);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime*30.0f);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}


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

#include  <stdlib.h>    
#include  <time.h>
#include "GameObject.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void renderCube();
void renderScene(Shader shader);
void RenderQuad();
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(-5.0f, 2.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
unsigned int planeVAO;
unsigned int quadVAO = 1, quadVBO = 1;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

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

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

	//float planeVertices[] = {
	//	// positions            // normals         // texcoords
	//	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	//	-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
	//	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

	//	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	//	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
	//	 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	//};
	//// plane VAO
	//unsigned int planeVBO;
	//glGenVertexArrays(1, &planeVAO);
	//glGenBuffers(1, &planeVBO);
	//glBindVertexArray(planeVAO);
	//glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glBindVertexArray(0);

	//Shader shader("shadow_mapping.vs", "shadow_mapping.fs"),
	//	simpleDepthShader("shadow_mapping_depth.vs", "shadow_mapping_depth.fs"),
	//	debugDepthQuad("debug_quad.vs", "debug_quad_depth.fs");

	//const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	//unsigned int depthMapFBO;
	//glGenFramebuffers(1, &depthMapFBO);
	//// create depth texture
	//unsigned int depthMap;
	//glGenTextures(1, &depthMap);
	//glBindTexture(GL_TEXTURE_2D, depthMap);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	//float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	//// attach depth texture as FBO's depth buffer
	//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//shader.use();
	//shader.setInt("diffuseTexture", 0);
	//shader.setInt("shadowMap", 1);
	//debugDepthQuad.use();
	//debugDepthQuad.setInt("depthMap", 0);

	//glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);


	// load models
	// -----------
	////Model rose(FileSystem::getPath("resources/objects/rose/rose.obj"));
	//Model palm(FileSystem::getPath("resources/objects/palm/Palm_01.obj"));
	////Model castle(FileSystem::getPath("resources/objects/castle/eastern ancient casttle.obj"));
	//Model city(FileSystem::getPath("resources/objects/city/Organodron City.obj"));

	//Model landscape(FileSystem::getPath("resources/objects/landscape/Ocean.obj"));
	Model fish(FileSystem::getPath("resources/objects/fish/fish.obj"));
	Model fish2(FileSystem::getPath("resources/objects/fish2/13009_Coral_Beauty_Angelfish_v1_l3.obj"));
	//Model fish3(FileSystem::getPath("resources/objects/fish3/12265_Fish_v1_L2.obj"));
	//Model fish4(FileSystem::getPath("resources/objects/fish4/13013_Red_Head_Solon_Fairy_Wrasse_v1_l3.obj"));
	////Model frog(FileSystem::getPath("resources/objects/frog/20436_Frog_v1 textured.obj"));
	//Model whale(FileSystem::getPath("resources/objects/whale/10054_Whale_v2_L3.obj"));
	//Model coralReef(FileSystem::getPath("resources/objects/coralReef/source/model.obj"));
	//Model coralReef2(FileSystem::getPath("resources/objects/coralReef2/source/model.obj"));
	//Model coralReef3(FileSystem::getPath("resources/objects/coralReef3/source/model.obj"));
	//Model seaDragon(FileSystem::getPath("resources/objects/seaDragon/source/model.obj"));
	//Model turtle(FileSystem::getPath("resources/objects/turtle/model.obj"));


	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------

	//srand((unsigned)time(NULL));
	//float randomCoorX[50], randomCoorY[50], randomCoorZ[50];
	//for (int i = 0; i < 50; i++) {
	//	randomCoorX[i] = rand() / double(RAND_MAX)*100.0f;
	//	randomCoorY[i] = rand() / double(RAND_MAX)*100.0f;
	//	randomCoorZ[i] = rand() / double(RAND_MAX)*100.0f;
	//}

	//SceneManager myScene(&camera);//这个是场景管理器

	//myScene.InitParticle();//初始化粒子

	//Skybox skybox; //天空盒

	GameObject obj1(false, glm::vec3(-5.0f, 2.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.1f), 5.0f, 0.0f, 180.0f);
	GameObject obj2(false, glm::vec3(-5.0f, 2.0f, 50.0f), glm::vec3(8.0f, 8.0f, 8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -0.1f), 5.0f, 0.0f, 180.0f);
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		// don't forget to enable shader before setting uniforms
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 1. render depth of scene to texture (from light's perspective)
		// --------------------------------------------------------------
		
		ourShader.use();
		
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 3000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		ourShader.setInt("texture_diffuse1", 0);
		glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
		ourShader.setVec3("lightPos", lightPos);
		ourShader.setVec3("viewPos", camera.Position);

		bool collision = obj1.DetectCollision(obj1, obj2);
		if (collision) {
			obj1.CollidedIn();
			obj2.CollidedIn();
		}
		else {
			obj1.CollidedOut();
			obj2.CollidedOut();
		}
		glm::mat4 model = glm::mat4(1.0f);
		cout << "obj1" << endl;
		model = obj1.Move();
		
		ourShader.setMat4("model", model);
		fish.Draw(ourShader);

		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
		//ourShader.setMat4("model", model);
		//fish.Draw(ourShader);
		cout << "obj2" << endl;
		model = obj2.Move();
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		fish2.Draw(ourShader);


		// view/projection transformations

		/*ourShader.setInt("texture_diffuse1", 0);
		glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
		ourShader.setVec3("lightPos", lightPos);
		ourShader.setVec3("viewPos", camera.Position);


		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 3000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		ourShader.use();*/



		// render the loaded model
		/*glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(500.0f, 500.0f, 500.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		landscape.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -10.0f, 1000.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		city.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(500.0f, -20.0f, 500.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		coralReef.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(400.0f, -20.0f, -300.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		coralReef2.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-600.0f, -130.0f, 650.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		coralReef3.Draw(ourShader);
		float x[3] = { 570.0f, 450.0f, -650.0f }, z[3] = { 480.0f, -250.0f, 600.0f };
		for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 50; j++) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x[i] + randomCoorX[j], -1.0f, z[i] + randomCoorZ[j])); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		palm.Draw(ourShader);
		}
		}

		for (int i = 0; i < 50; i++) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-300.0f + randomCoorX[i], 130.0f + randomCoorY[i], 550.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		fish.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-100.0f + randomCoorX[i], 530.0f + randomCoorY[i], 250.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", model);
		fish.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(500.0f + randomCoorX[i], 30.0f + randomCoorY[i], -400.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		fish2.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(500.0f + randomCoorX[i], 250.0f + randomCoorY[i], 450.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		fish3.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-500.0f + randomCoorX[i], 400.0f + randomCoorY[i], -450.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		fish4.Draw(ourShader);
		}

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-50.0f, 700.0f, 300.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		whale.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(450.0f, 50.0f, 500.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		turtle.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(380.0f, 80.0f, 400.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		turtle.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-100.0f, 100.0f, 600.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		seaDragon.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 50.0f, 500.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		seaDragon.Draw(ourShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-50.0f, 100.0f, 520.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		seaDragon.Draw(ourShader);*/

		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

		/*ourShader.setMat4("model", model);
		ourShader.setInt("texture_diffuse1", 0);
		glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
		ourShader.setVec3("lightPos", lightPos);
		ourShader.setVec3("viewPos", camera.Position);*/

		//city.Draw(ourShader);


		//Transform debugTransform;
		//myScene.temptation->Update(deltaTime, debugTransform, 8, glm::vec3(1.0f, 1.0f, 1.0f), 2);
		////渲染场景中的所有模型
		//myScene.DrawElements();//只需要调用这个函数就可以画出所有元素

		//skybox.drawSkybox(projection, view);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime*30.0f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime*30.0f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime*30.0f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime*30.0f);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void renderScene(Shader shader)
{
	// Floor
	glm::mat4 model = glm::mat4(1.0f);
	shader.setMat4("model", model);
	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// cubes
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
	shader.setMat4("model", model);
	renderCube();
}
void renderCube() {
	unsigned int cubeVAO, cubeVBO;
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
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
void RenderQuad()
{
	if (quadVAO == 0)
	{
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		};
		// Setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}