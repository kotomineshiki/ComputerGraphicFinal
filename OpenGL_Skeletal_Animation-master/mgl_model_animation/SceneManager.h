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

class SceneManager{
public:
	//Model rose;
	Model palm;
	Model fish;
	Model fish2;
	Model fish3;
	Model fish4;
	SkinnedMesh whale;
	//Model city;
	Model landscape;
	Model coralReef;
	/*Model coralReef2;
	Model coralReef3;*/
	Model seaDragon;
	Model turtle;

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
	Texture2D particleTexture;
	std::shared_ptr<ParticleGenerator> temptation;
	float randomCoorX[50], randomCoorY[50], randomCoorZ[50], x[3], z[3];
	static const uint MAX_BONES = 100;
	float m_startTime;
	//Shader shadowShader;
	Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha)//从资源中读入texture
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
	SceneManager(Camera* input) : //rose("resources/Models/rose/rose.obj"),
		palm("resources/Models/palm/Palm_01.obj"),
		fish("resources/Models/fish/fish.obj"),
		fish2("resources/Models/fish2/13009_Coral_Beauty_Angelfish_v1_l3.obj"),
		fish3("resources/Models/fish3/12265_Fish_v1_L2.obj"),
		fish4("resources/Models/fish4/13013_Red_Head_Solon_Fairy_Wrasse_v1_l3.obj"),
		//city("resources/Models/city/Organodron City.obj"),
		landscape("resources/Models/landscape/Ocean.obj"),
		coralReef("resources/Models/coralReef/source/model.obj"),
		//coralReef2("resources/Models/coralReef2/source/model.obj"),
		//coralReef3("resources/Models/coralReef3/source/model.obj"),
		seaDragon("resources/Models/seaDragon/source/model.obj"),
		turtle("resources/Models/turtle/model.obj"),
		shader1("1.model_loading.vs", "1.model_loading.fs"),
		shader2("skinning.vs", "skinning2"),
		particleShader("Particle.vs","Particle.fs")
	{//初始化这个场景
		whale.LoadMesh("resources/Models/Humpback whale/5.fbx");
		camera = input;
		particleTexture = loadTextureFromFile("resources/Textures/particle.bmp", GL_FALSE);//获取粒子效果所使用的贴图
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
	}

	//void DrawRose() {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	//	shader1.setMat4("model", model);
	//	rose.Draw(shader1);
	//}
	void DrawPalm() {
		shader1.use();
		glm::mat4 model = glm::mat4(1.0f);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 50; j++) {
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(x[i] + randomCoorX[j], -1.0f, z[i] + randomCoorZ[j])); // translate it down so it's at the center of the scene
				model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));	// it's a bit too big for our scene, so scale it down
				shader1.setMat4("model", model);
				palm.Draw(shader1);
			}
		}
	}
	void DrawFish() {
		shader1.use();
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
			shader1.setMat4("model", model);
			fish.Draw(shader1);
		}
	}
	void DrawFish2() {
		shader1.use();
		glm::mat4 model = glm::mat4(1.0f);
		for (int i = 0; i < 50; i++) {
			//model = glm::mat4(1.0f);
			//model = glm::translate(model, glm::vec3(280.0f + randomCoorX[i], 30.0f + randomCoorY[i], -150.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
			//model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));	// it's a bit too big for our scene, so scale it down
			model = fishObj2[i].Move();
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			shader1.setMat4("model", model);
			fish2.Draw(shader1);
		}
	}

	void DrawFish3() {
		shader1.use();
		glm::mat4 model = glm::mat4(1.0f);
		for (int i = 0; i < 50; i++) {
			//model = glm::mat4(1.0f);
			//model = glm::translate(model, glm::vec3(200.0f + randomCoorX[i], 200.0f + randomCoorY[i], 250.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
			//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
			model = fishObj3[i].Move();
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			shader1.setMat4("model", model);
			fish3.Draw(shader1);
		}
	}
	void DrawFish4() {
		shader1.use();
		glm::mat4 model = glm::mat4(1.0f);
		for (int i = 0; i < 50; i++) {
			//model = glm::mat4(1.0f);
			//model = glm::translate(model, glm::vec3(-280.0f + randomCoorX[i], 300.0f + randomCoorY[i], -100.0f + randomCoorZ[i])); // translate it down so it's at the center of the scene
			//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
			model = fishObj4[i].Move();
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			shader1.setMat4("model", model);
			fish4.Draw(shader1);
		}
	}
	void DrawWhale() {
		GLuint m_boneLocation[MAX_BONES];
		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation); i++) {
			char Name[128];
			memset(Name, 0, sizeof(Name));
			SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);

			m_boneLocation[i] = glGetUniformLocation(shader2.ID, Name);
		}

		float RunningTime = (float)((double)glfwGetTime() - (double)m_startTime);// / 1000.0f;
		vector<Matrix4f> Transforms;

		whale.BoneTransform(RunningTime, Transforms);

		for (uint i = 0; i < Transforms.size(); i++) {
			//m_pEffect->SetBoneTransform(i, Transforms[i]);
			glUniformMatrix4fv(m_boneLocation[i], 1, GL_TRUE, (const GLfloat*)Transforms[i]);
		}

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 100.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.1f, 3000.0f);
		glm::mat4 view = camera->GetViewMatrix();
		shader2.use();
		shader2.setMat4("projection", projection);
		shader2.setMat4("view", view);
		shader2.setMat4("model", model);
		whale.Render();
	}
	//void DrawCity() {
	//  shader1.use();
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(-110.0f, -5.0f, -100.0f)); // translate it down so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
	//	shader1.setMat4("model", model);
	//	city.Draw(shader1);
	//}
	void DrawLandscape() {
		shader1.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(250.0f, 250.0f, 250.0f));	// it's a bit too big for our scene, so scale it down
		shader1.setMat4("model", model);
		landscape.Draw(shader1);
	}
	void DrawCoralReef() {
		shader1.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(325.0f, -30.0f, 300.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shader1.setMat4("model", model);
		coralReef.Draw(shader1);
	}
	//void DrawCoralReef2() {
	//  shader1.use();
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(-300.0f, -40.0f, 210.0f)); // translate it down so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));	// it's a bit too big for our scene, so scale it down
	//	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//	shader1.setMat4("model", model);
	//	coralReef2.Draw(shader1);
	//}
	//void DrawCoralReef3() {
	//  shader1.use();
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(300.0f, -130.0f, -310.0f)); // translate it down so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(2.2f, 2.2f, 2.2f));	// it's a bit too big for our scene, so scale it down
	//	model = glm::rotate(model, glm::radians(-120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//	shader1.setMat4("model", model);
	//	coralReef3.Draw(shader1);
	//}
	void DrawSeaDragon() {
		shader1.use();
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-100.0f, 100.0f, 290.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
		model = seaDragonObj.Move();
		shader1.setMat4("model", model);
		seaDragon.Draw(shader1);
	}
	void DrawTurtle() {
		shader1.use();
		glm::mat4 model = glm::mat4(1.0f);
		if (turtleObj.DetectCollision(turtleObj, coralReefObj)|| turtleObj.DetectCollision(turtleObj, coralReefObj2)) {
			turtleObj.CollidedIn();
		}
		else {
			turtleObj.CollidedOut();
		}
		//model = glm::translate(model, glm::vec3(100.0f, 30.0f, 250.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
		model = turtleObj.Move();
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shader1.setMat4("model", model);
		turtle.Draw(shader1);
	}
	void InitShaders() {
		shader1.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.1f, 3000.0f);
		glm::mat4 view = camera->GetViewMatrix();
		shader1.setMat4("projection", projection);
		shader1.setMat4("view", view);
		shader1.setInt("texture_diffuse1", 0);
		glm::vec3 lightPos(0.0f, 0.0f, 5.0f);
		shader1.setVec3("lightPos", lightPos);
		shader1.setVec3("viewPos", camera->Position);
	}
	void DrawElements() {//严格来说函数指针似乎更好
		InitShaders();
	    //*DrawRose();
		DrawPalm();
		DrawFish();
		DrawFish2();
		DrawFish3();
		DrawFish4();
		//DrawCity();
		DrawLandscape();
		DrawCoralReef();
		//DrawCoralReef2();
		//DrawCoralReef3();
		DrawSeaDragon();
		DrawTurtle();
		DrawWhale();
		//temptation->Draw();
	}
	void InitParticle() {
		temptation = std::make_shared<ParticleGenerator>(//初始化
			particleShader,
			particleTexture,
			5,
			camera,
			30,
			5.0f,
			1.0 / 5.0f
			);
	}
};

/*	Model rose(FileSystem::getPath("resources/objects/rose/rose.obj"));
	Model palm(FileSystem::getPath("resources/objects/palm/Palm_01.obj"));
	//Model castle(FileSystem::getPath("resources/objects/castle/eastern ancient casttle.obj"));
	Model fish(FileSystem::getPath("resources/objects/fish/fish.obj"));
	Model fish2(FileSystem::getPath("resources/objects/fish2/13009_Coral_Beauty_Angelfish_v1_l3.obj"));
	Model fish3(FileSystem::getPath("resources/objects/fish3/12265_Fish_v1_L2.obj"));
	Model fish4(FileSystem::getPath("resources/objects/fish4/13013_Red_Head_Solon_Fairy_Wrasse_v1_l3.obj"));
	//Model frog(FileSystem::getPath("resources/objects/frog/20436_Frog_v1 textured.obj"));
	Model whale(FileSystem::getPath("resources/objects/whale/10054_Whale_v2_L3.obj"));
	//Model coralReef(FileSystem::getPath("resources/objects/coralReef/source/model.obj"));
	//Model coralReef2(FileSystem::getPath("resources/objects/coralReef2/source/model.obj"));
	//Model coralReef3(FileSystem::getPath("resources/objects/coralReef3/source/model.obj"));
	//Model plant(FileSystem::getPath("resources/objects/plant/model.obj"));
	//Model seaDragon(FileSystem::getPath("resources/objects/seaDragon/source/model.obj"));
	//Model turtle(FileSystem::getPath("resources/objects/turtle/model.obj"));
	*/