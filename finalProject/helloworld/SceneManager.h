#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include"ParticleGenerator.h"
class SceneManager{
public:
	Model rose;
	Model palm;
	Model fish;
	Model fish2;
	Model fish3;
	Model fish4;
	Model whale;
	Camera* camera;
	Shader shader1;
	Shader particleShader;
	Texture2D particleTexture;
	std::shared_ptr<ParticleGenerator> temptation;
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
		GLenum format;
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
	SceneManager(Camera* input) : rose(FileSystem::getPath("resources/objects/rose/rose.obj")),
		palm(FileSystem::getPath("resources/objects/palm/Palm_01.obj")),
		fish(FileSystem::getPath("resources/objects/fish/fish.obj")),
		fish2(FileSystem::getPath("resources/objects/fish2/13009_Coral_Beauty_Angelfish_v1_l3.obj")),
		fish3(FileSystem::getPath("resources/objects/fish3/12265_Fish_v1_L2.obj")),
		fish4(FileSystem::getPath("resources/objects/fish4/13013_Red_Head_Solon_Fairy_Wrasse_v1_l3.obj")),
		whale(FileSystem::getPath("resources/objects/whale/10054_Whale_v2_L3.obj")),
		shader1("1.model_loading.vs", "1.model_loading.fs"),
		particleShader("Particle.vs","Particle.fs")
	{//初始化这个场景
		camera = input;
		particleTexture = loadTextureFromFile("resources/Textures/particle.bmp", GL_FALSE);//获取粒子效果所使用的贴图
	}

	void DrawRose() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		shader1.setMat4("model", model);
		rose.Draw(shader1);

	}
	void DrawPalm() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		shader1.setMat4("model", model);
		palm.Draw(shader1);
	}
	void DrawFish() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, 15.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));	// it's a bit too big for our scene, so scale it down
		shader1.setMat4("model", model);
		fish.Draw(shader1);
	}
	void DrawFish2() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 18.0f, -20.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shader1.setMat4("model", model);
		fish2.Draw(shader1);
	}

	void DrawFish3() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(20.0f, 30.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shader1.setMat4("model", model);
		fish3.Draw(shader1);
	}
	void DrawFish4() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-50.0f, 30.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shader1.setMat4("model", model);
		fish4.Draw(shader1);
	}
	void DrawWhale() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-50.0f, 180.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shader1.setMat4("model", model);
		whale.Draw(shader1);
	}
	void InitShaders() {
		shader1.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.1f, 1000.0f);
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
		DrawRose();
		DrawPalm();
		DrawFish();

		DrawFish2();
		DrawFish3();
		DrawFish4();
		DrawWhale();
		temptation->Draw();
	}
	void InitParticle() {
		temptation = std::make_shared<ParticleGenerator>(//初始化
			particleShader,
			particleTexture,
			800,
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