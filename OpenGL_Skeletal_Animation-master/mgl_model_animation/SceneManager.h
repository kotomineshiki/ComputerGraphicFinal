#pragma once
//#include <glad/glad.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"camera.h"
#include"shader.h"
#include"model.h"
#include"ParticleGenerator.h"
#include "GameObject.h"
#include "Skybox.h"
#include "Text.h"
#include <time.h>
#include <stdlib.h>
#include"Wave.h"
class SceneManager{
public:
	//Model palm;
	Model fish;
	Model fish2;
	//Model fish3;
	//Model fish4;
	SkinnedMesh whale;
	SkinnedMesh harpyCat;
	Model city;
	Model landscape;
	//Model coralReef;
	/*Model coralReef2;
	Model coralReef3;

	//Model seaDragon;
	//Model turtle;
	Wave testWave;

	Model seaDragon;
	Model turtle;*/


	GameObject fishObj[50];
	GameObject fishObj2[50];
	GameObject fishObj3[50];
	GameObject fishObj4[50];
	GameObject cityObj;
	GameObject coralReefObj;
	GameObject coralReefObj2;
	GameObject coralReefObj3;
	GameObject seaDragonObj;
	GameObject turtleObj;

	Camera* camera;
	Shader shader1;
	Shader shader2;
	Shader particleShader;
	Shader stencilShader;
	Shader shadowShader;
	Shader waveShader;
	Shader shadowDepthShader;
	Shader shadowDepthShaderDynamic;
	Shader shadowDebugShader;
	Shader dynamicShadowShader;
	Texture2D particleTexture;
	std::shared_ptr<ParticleGenerator> temptation;
	float randomCoorX[50], randomCoorY[50], randomCoorZ[50], x[3], z[3];
	static const uint MAX_BONES = 100;
	float m_startTime;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	unsigned int depthMap;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	float near_plane = -500.0f, far_plane = 500.0f;
	glm::vec3 lightPos;
	Text text;
	Shader shaderText;
	Skybox skybox;
	Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha)//����Դ�ж���texture
	{
		// Create Texture object
		Texture2D texture;
		if (alpha) {
			texture.Internal_Format = GL_RGBA;
			texture.Image_Format = GL_RGBA;
		}
		int nrComponents;
		// Load image
		int width, height;
		unsigned char *image = stbi_load(file, &width, &height, &nrComponents, 0);
		GLenum format=4;
		switch (nrComponents) {
		case 1:format = GL_RED; break;
		case 3:format = GL_RGB; break;
		case 4:format = GL_RGBA; break;
		}
		// Now generate texture
		texture.Generate(width, height, image, format);
		// And finally free image data
		stbi_image_free(image);
		return texture;
	}
	SceneManager(Camera* input) :
		//palm("resources/Models/palm/Palm_01.obj"),
		fish("resources/Models/fish/fish.obj"),
		fish2("resources/Models/fish2/13009_Coral_Beauty_Angelfish_v1_l3.obj"),
		//fish3("resources/Models/fish3/12265_Fish_v1_L2.obj"),
		//fish4("resources/Models/fish4/13013_Red_Head_Solon_Fairy_Wrasse_v1_l3.obj"),
		city("resources/Models/city/Organodron City.obj"),
		landscape("resources/Models/landscape/Ocean.obj"),
		//coralReef("resources/Models/coralReef/source/model.obj"),
		/*coralReef2("resources/Models/coralReef2/source/model.obj"),
		coralReef3("resources/Models/coralReef3/source/model.obj"),
		seaDragon("resources/Models/seaDragon/source/model.obj"),
		turtle("resources/Models/turtle/model.obj"),*/
		shader1("1.model_loading.vs", "1.model_loading.fs"),
		shader2("skinning.vs", "skinning2"),
		waveShader("wave.vs","wave.fs"),
		particleShader("Particle.vs", "Particle.fs"),
		stencilShader("stencilTest.vs", "stencilTest.fs"),
		shadowShader("shadow_mapping.vs", "shadow_mapping.fs"),
		shadowDepthShader("shadow_mapping_depth.vs", "shadow_mapping_depth.fs"),
		shadowDepthShaderDynamic("shadow_mapping_depth_dynamic.vs", "shadow_mapping_depth.fs"),
		shadowDebugShader("debug_quad.vs", "debug_quad_depth.fs"),
		dynamicShadowShader("shadow_mapping_dynamic.vs","shadow_mapping_dynamic.fs"),
		shaderText("Text.vs", "Text.fs")
	{
		whale.LoadMesh("resources/Models/Humpback whale/5.fbx");
		harpyCat.LoadMesh("resources/Models/test/HarpyCat/Model/1.fbx");
		camera = input;
		particleTexture = loadTextureFromFile("resources/Textures/particle.bmp", GL_FALSE);
		srand((unsigned)time(NULL));
		for (int i = 0; i < 50; i++) {
			randomCoorX[i] = rand() / double(RAND_MAX)*100.0f;
			randomCoorY[i] = rand() / double(RAND_MAX)*100.0f;
			randomCoorZ[i] = rand() / double(RAND_MAX)*100.0f;
		}
		x[0] = 280.0f;
		x[1] = 330.0f;
		x[2] = -310.0f;
		z[0] = 310.0f;
		z[1] = -280.0f;
		z[2] = 280.0f;
		m_startTime = glfwGetTime();

		for (int i = 0; i < 50; i++) {
			fishObj[i].setObject(false, glm::vec3(-300.0f + randomCoorX[i], 100.0f + randomCoorY[i], 170.0f + randomCoorZ[i]), glm::vec3(2.5f, 2.5f, 2.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.5f), 2.5f, 0.0f, 180.0f);
			fishObj2[i].setObject(false, glm::vec3(280.0f + randomCoorX[i], 30.0f + randomCoorY[i], -150.0f + randomCoorZ[i]), glm::vec3(6.0f, 6.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.5f), 6.0f, 0.0f, 180.0f);
			fishObj3[i].setObject(false, glm::vec3(200.0f + randomCoorX[i], 200.0f + randomCoorY[i], 250.0f + randomCoorZ[i]), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.5f, 0.0f, 0.0f), 0.5f, 0.0f, 180.0f);
			fishObj4[i].setObject(false, glm::vec3(-280.0f + randomCoorX[i], 300.0f + randomCoorY[i], -100.0f + randomCoorZ[i]), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.5f, 0.0f, 0.0f), 1.0f, 0.0f, 180.0f);
		}

		cityObj.setObject(true, glm::vec3(-110.0f, -5.0f, -100.0f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.5f), 250.0f, 0.0f, 180.0f);
		coralReefObj.setObject(true, glm::vec3(325.0f, -30.0f, 300.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.5f), 100.0f, 0.0f, 180.0f);
		coralReefObj2.setObject(true, glm::vec3(-300.0f, -40.0f, 210.0f), glm::vec3(6.0f, 6.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.5f), 110.0f, 0.0f, 180.0f);
		coralReefObj3.setObject(true, glm::vec3(300.0f, -130.0f, -310.0f), glm::vec3(2.2f, 2.2f, 2.2f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.5f), 105.0f, 0.0f, 180.0f);

		seaDragonObj.setObject(false, glm::vec3(-100.0f, 100.0f, 290.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 10.0f, 0.0f, 180.0f);
		turtleObj.setObject(false, glm::vec3(100.0f, 30.0f, 250.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 10.0f, 0.0f, 180.0f);

		glGenFramebuffers(1, &depthMapFBO);
		// create depth texture
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		// attach depth texture as FBO's depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		shadowShader.use();
		shadowShader.setInt("diffuseTexture", 0);
		shadowShader.setInt("shadowMap", 1);
		shadowDebugShader.use();
		shadowDebugShader.setInt("depthMap", 0);
		dynamicShadowShader.use();
		dynamicShadowShader.setInt("diffuseTexture", 0);
		dynamicShadowShader.setInt("shadowMap", 1);

		//lightPos = glm::vec3(-110.0f, 800.0f, -100.0f);
		lightPos = glm::vec3(-110.0f, 200.0f, -100.0f);

		// Initialize text
		text.LoadText(shaderText, SCR_WIDTH, SCR_HEIGHT);
	}

	//void DrawPalm(const Shader &shader) {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	for (int i = 0; i < 3; i++) {
	//		for (int j = 0; j < 50; j++) {
	//			model = glm::mat4(1.0f);
	//			model = glm::translate(model, glm::vec3(x[i] + randomCoorX[j], -1.0f, z[i] + randomCoorZ[j])); // translate it down so it's at the center of the scene
	//			model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));	// it's a bit too big for our scene, so scale it down
	//			shader.setMat4("model", model);
	//			palm.Draw(shader);
	//		}
	//	}
	//}
	void DrawFish(const Shader &shader) {
		glm::mat4 model = glm::mat4(1.0f);
		for (int i = 0; i < 50; i++) {
			if (fishObj[i].DetectCollision(fishObj[i], coralReefObj) || fishObj[i].DetectCollision(fishObj[i], coralReefObj3)) {
				fishObj[i].CollidedIn();
			}
			else {
				fishObj[i].CollidedOut();
			}
			//model = glm::mat4(1.0f);
			//model = glm::translate(model, glm::vec3(-300.0f + randomCoorX[i], 100.0f + randomCoorY[i], 170.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
			//model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));	// it's a bit too big for our scene, so scale it down
			model = fishObj[i].Move();
			shader.setMat4("model", model);
			fish.Draw(shader);
		}
	}
	void DrawFish2(const Shader &shader) {
		glm::mat4 model = glm::mat4(1.0f);
		for (int i = 0; i < 50; i++) {
			//model = glm::mat4(1.0f);
			//model = glm::translate(model, glm::vec3(280.0f + randomCoorX[i], 30.0f + randomCoorY[i], -150.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
			//model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));	// it's a bit too big for our scene, so scale it down
			model = fishObj2[i].Move();
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			shader.setMat4("model", model);
			fish2.Draw(shader);
		}
	}

	//void DrawFish3(const Shader &shader) {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	for (int i = 0; i < 50; i++) {
	//		//model = glm::mat4(1.0f);
	//		//model = glm::translate(model, glm::vec3(200.0f + randomCoorX[i], 200.0f + randomCoorY[i], 250.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
	//		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
	//		model = fishObj3[i].Move();
	//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//		shader.setMat4("model", model);
	//		fish3.Draw(shader);
	//	}
	//}
	//void DrawFish4(const Shader &shader) {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	for (int i = 0; i < 50; i++) {
	//		//model = glm::mat4(1.0f);
	//		//model = glm::translate(model, glm::vec3(-280.0f + randomCoorX[i], 300.0f + randomCoorY[i], -100.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
	//		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	//		model = fishObj4[i].Move();
	//		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//		shader.setMat4("model", model);
	//		fish4.Draw(shader);
	//	}
	//}
	void DrawWhale(const Shader &shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.0f, 100.0f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 0.1f*(float)glfwGetTime()*glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(300.0f, 600.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	//it's a bit too big for our scene, so scale it down
		shader.setMat4("model", model);
		whale.Render();
	}
	void DrawHarpyCat(const Shader &shader) {
		GLuint m_boneLocation[MAX_BONES];
		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation); i++) {
			char Name[128];
			memset(Name, 0, sizeof(Name));
			SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);

			m_boneLocation[i] = glGetUniformLocation(shader.ID, Name);
		}
		float RunningTime = (float)((double)glfwGetTime() - (double)m_startTime);// / 1000.0f;
		vector<Matrix4f> Transforms;
		harpyCat.BoneTransform(RunningTime, Transforms);

		for (uint i = 0; i < Transforms.size(); i++) {
			//m_pEffect->SetBoneTransform(i, Transforms[i]);
			glUniformMatrix4fv(m_boneLocation[i], 1, GL_TRUE, (const GLfloat*)Transforms[i]);
		}

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.0f, 100.0f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, 1.0f*(float)glfwGetTime()*glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 20.0f, -100.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	//it's a bit too big for our scene, so scale it down
		shader.setMat4("model", model);
		harpyCat.Render();
	}
	void DrawCity(Shader &shader) {
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::translate(model, glm::vec3(-110.0f, -5.0f, -100.0f)); // translate it down so it's at the center of the scene
		shader.setMat4("model", model);
		city.Draw(shader);

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//glStencilMask(0x00);
		glStencilMask(0xFF);
		glDisable(GL_DEPTH_TEST);
		stencilShader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.1f, 3000.0f);
		glm::mat4 view = camera->GetViewMatrix();
		stencilShader.setMat4("projection", projection);
		stencilShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.705f, 0.705f, 0.705f));
		model = glm::translate(model, glm::vec3(-110.0f, -5.0f, -100.0f)); // translate it down so it's at the center of the scene
		stencilShader.setMat4("model", model);
		city.Draw(stencilShader);
		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);

		shader.use();
	}
	void DrawLandscape(const Shader &shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(250.0f, 10.0f, 250.0f));	// it's a bit too big for our scene, so scale it down
		double time = glfwGetTime();
		std::cout << time << endl;
		shader.setFloat("time", time);
		shader.setMat4("model", model);
		landscape.Draw(shader);
	}
	//void DrawCoralReef(const Shader &shader) {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(325.0f, -30.0f, 300.0f)); // translate it down so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
	//	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//	shader.setMat4("model", model);
	//	coralReef.Draw(shader);
	//}
	//void DrawCoralReef2(const Shader &shader) {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(-300.0f, -40.0f, 210.0f)); // translate it down so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));	// it's a bit too big for our scene, so scale it down
	//	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//	shader.setMat4("model", model);
	//	coralReef2.Draw(shader);
	//}
	//void DrawCoralReef3(const Shader &shader) {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(300.0f, -130.0f, -310.0f)); // translate it down so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(2.2f, 2.2f, 2.2f));	// it's a bit too big for our scene, so scale it down
	//	model = glm::rotate(model, glm::radians(-120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//	shader.setMat4("model", model);
	//	coralReef3.Draw(shader);
	//}
	//void DrawSeaDragon(const Shader &shader) {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	//model = glm::translate(model, glm::vec3(-100.0f, 100.0f, 290.0f)); // translate it down so it's at the center of the scene
	//	//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
	//	model = seaDragonObj.Move();
	//	shader.setMat4("model", model);
	//	seaDragon.Draw(shader);
	//}
	//void DrawTurtle(const Shader &shader) {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	if (turtleObj.DetectCollision(turtleObj, coralReefObj)|| turtleObj.DetectCollision(turtleObj, coralReefObj2)) {
	//		turtleObj.CollidedIn();
	//	}
	//	else {
	//		turtleObj.CollidedOut();
	//	}
	//	//model = glm::translate(model, glm::vec3(100.0f, 30.0f, 250.0f)); // translate it down so it's at the center of the scene
	//	//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
	//	model = turtleObj.Move();
	//	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//	shader.setMat4("model", model);
	//	turtle.Draw(shader);
	//}
	void InitShaders() {
		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		//lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
		lightProjection = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, near_plane, far_plane);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		lightSpaceMatrix = lightProjection * lightView;
		// render scene from light's point of view
		shadowDepthShaderDynamic.use();
		shadowDepthShaderDynamic.setMat4("lightSpaceMatrix", lightSpaceMatrix);

		shadowDepthShader.use();
		shadowDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	void InitShaders2() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadowShader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera->GetViewMatrix();
		shadowShader.setMat4("projection", projection);
		shadowShader.setMat4("view", view);
		//skybox.Draw(projection, view);
		// set light uniforms

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		//lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
		lightProjection = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, near_plane, far_plane);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		lightSpaceMatrix = lightProjection * lightView;

		shadowShader.setVec3("viewPos", camera->Position);
		shadowShader.setVec3("lightPos", lightPos);
		shadowShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		//skybox.Draw(projection, view);
	}
	void InitShaders3() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		dynamicShadowShader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera->GetViewMatrix();
		dynamicShadowShader.setMat4("projection", projection);
		dynamicShadowShader.setMat4("view", view);
		// set light uniforms

		
		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		//lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
		lightProjection = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, near_plane, far_plane);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		lightSpaceMatrix = lightProjection * lightView;

		dynamicShadowShader.setVec3("viewPos", camera->Position);
		dynamicShadowShader.setVec3("lightPos", lightPos);
		dynamicShadowShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		GLuint m_boneLocation[MAX_BONES];
		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation); i++) {
			char Name[128];
			memset(Name, 0, sizeof(Name));
			SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);

			m_boneLocation[i] = glGetUniformLocation(dynamicShadowShader.ID, Name);
		}
		float RunningTime = (float)((double)glfwGetTime() - (double)m_startTime);// / 1000.0f;
		vector<Matrix4f> Transforms;

		whale.BoneTransform(RunningTime, Transforms);
		//harpyCat.BoneTransform(RunningTime, Transforms);

		for (uint i = 0; i < Transforms.size(); i++) {
			//m_pEffect->SetBoneTransform(i, Transforms[i]);
			glUniformMatrix4fv(m_boneLocation[i], 1, GL_TRUE, (const GLfloat*)Transforms[i]);
		}
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
	}
	void InitDynamicDepthShader() {
		shadowDepthShaderDynamic.use();
		GLuint m_boneLocation[MAX_BONES];
		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation); i++) {
			char Name[128];
			memset(Name, 0, sizeof(Name));
			SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);

			m_boneLocation[i] = glGetUniformLocation(shadowDepthShaderDynamic.ID, Name);
		}
		float RunningTime = (float)((double)glfwGetTime() - (double)m_startTime);// / 1000.0f;
		vector<Matrix4f> Transforms;

		whale.BoneTransform(RunningTime, Transforms);
		//harpyCat.BoneTransform(RunningTime, Transforms);

		for (uint i = 0; i < Transforms.size(); i++) {
			//m_pEffect->SetBoneTransform(i, Transforms[i]);
			glUniformMatrix4fv(m_boneLocation[i], 1, GL_TRUE, (const GLfloat*)Transforms[i]);
		}
	}
	void DrawElements() {
		InitShaders();

		//DrawPalm(shadowDepthShader);
		DrawFish(shadowDepthShader);
		DrawFish2(shadowDepthShader);
		//DrawFish3(shadowDepthShader);
		//DrawFish4(shadowDepthShader);
		DrawCity(shadowDepthShader);
		DrawLandscape(shadowDepthShader);
		//DrawCoralReef(shadowDepthShader);
		//DrawCoralReef2(shadowDepthShader);
		//DrawCoralReef3(shadowDepthShader);
		//DrawSeaDragon(shadowDepthShader);
		//DrawTurtle(shadowDepthShader);

		//testWave.Update();
		//testWave.DrawLandscape(shadowShader);
		
		InitDynamicDepthShader();
		DrawWhale(shadowDepthShaderDynamic);
		DrawHarpyCat(shadowDepthShaderDynamic);
		
		InitShaders2();

		//DrawPalm(shadowShader);
		DrawFish(shadowShader);
		DrawFish2(shadowShader);
		//DrawFish3(shadowShader);
		//DrawFish4(shadowShader);
	    DrawCity(shadowShader);
		DrawLandscape(shadowShader);
		//DrawCoralReef(shadowShader);
		/*DrawCoralReef2(shadowShader);
		DrawCoralReef3(shadowShader);
		DrawSeaDragon(shadowShader);
		DrawTurtle(shadowShader);*/

		InitShaders3();
		DrawWhale(dynamicShadowShader);
		DrawHarpyCat(dynamicShadowShader);

		//Eject camera if collide
		/*for (int i = 0; i < 50; i++)
			GameObject::CameraCollision(fishObj[i], fishObj2[i], fishObj3[i], fishObj4[i]);
		GameObject::CameraCollision(cityObj, coralReefObj, coralReefObj2, coralReefObj3, seaDragonObj, turtleObj);*/
		

		shadowDebugShader.use();
		shadowDebugShader.setFloat("near_plane", near_plane);
		shadowDebugShader.setFloat("far_plane", far_plane);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera->GetViewMatrix();
		glStencilMask(0x00);
		skybox.Draw(projection, view);

		glDisable(GL_STENCIL_TEST);
		
		// text effect, should be rendered at last
		text.drawSample(shaderText, SCR_WIDTH, SCR_HEIGHT);
		
		//temptation->Draw();
	}
	void InitParticle() {
		temptation = std::make_shared<ParticleGenerator>(
			particleShader,
			particleTexture,
			100,
			camera,
			30,
			5.0f,
			1.0 / 5.0f
			);
	}
};
