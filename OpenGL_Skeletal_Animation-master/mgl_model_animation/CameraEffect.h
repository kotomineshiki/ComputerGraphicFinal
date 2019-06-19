#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "camera.h"
#include "Texture_c.h"
#include "stb_image.h"

# define M_PI           3.14159265358979323846

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

//static void GLCheckError() {
//	while (GLenum error = glGetError()) {
//		std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
//	}
//}

class CameraEffect
{
public:
	const int SCR_WIDTH = 1024;
	const int SCR_HEIGHT = 768;
	unsigned int lenscolor;
	unsigned int lensdirt;
	unsigned int lensstar;
	Shader plainShaders;
	Shader thresholdShaders;
	Shader featureGenerationShaders;
	Shader blendShader;
	Shader blurShader;
	Shader finalShader;
	unsigned int screenTexture;
	unsigned int motionBlurTextureBuffer;
	unsigned int fakeLightsBuffer;
	unsigned int fakeLightsTextureBuffer;
	unsigned int thresholdBuffer;
	unsigned int thresholdTextureBuffer;
	unsigned int featureGenerationBuffer;
	unsigned int featureGenerationTextureBuffer;
	unsigned int lensFlareShaderBuffer;
	unsigned int lensFlareShaderTextureBuffer;
	unsigned int screenVao;
	CameraEffect() :
		lenscolor(loadTexture("resources/CameraEffect/textures/lenscolor.png")),
		lensdirt(loadTexture("resources/CameraEffect/textures/lensdirt.png")),
		lensstar(loadTexture("resources/CameraEffect/textures/lensstar.png")),
		plainShaders("resources/CameraEffect/shaders/screenVertex.vs", "resources/CameraEffect/shaders/plainShader.fs"),
		thresholdShaders("resources/CameraEffect/shaders/screenVertex.vs", "resources/CameraEffect/shaders/thresholdShader.fs"),
		featureGenerationShaders("resources/CameraEffect/shaders/screenVertex.vs", "resources/CameraEffect/shaders/featureGenerationShader.fs"),
		blendShader("resources/CameraEffect/shaders/screenVertex.vs", "resources/CameraEffect/shaders/blendShader.fs"),
		blurShader("resources/CameraEffect/shaders/screenVertex.vs", "resources/CameraEffect/shaders/blurFragment.fs"),
		finalShader("resources/CameraEffect/shaders/screenVertex.vs", "resources/CameraEffect/shaders/final.fs")
	{
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// create a color attachment texture
		glGenTextures(1, &screenTexture);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, screenTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo4;
		glGenRenderbuffers(1, &rbo4);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo4);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo4); // now actually attach it
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		//-----------------------------------------------------------------------------------
		unsigned int motionblurBuffer;
		glGenFramebuffers(1, &motionblurBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, motionblurBuffer);
		// create a color attachment texture
		glGenTextures(1, &motionBlurTextureBuffer);
		glActiveTexture(GL_TEXTURE11);
		glBindTexture(GL_TEXTURE_2D, motionBlurTextureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, motionBlurTextureBuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo5;
		glGenRenderbuffers(1, &rbo5);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo5);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo5); // now actually attach it
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// ---------------------FakeLights--------------
		glGenFramebuffers(1, &fakeLightsBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, fakeLightsBuffer);
		// create a color attachment texture
		glActiveTexture(GL_TEXTURE3);
		glGenTextures(1, &fakeLightsTextureBuffer);
		glBindTexture(GL_TEXTURE_2D, fakeLightsTextureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fakeLightsTextureBuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo6;
		glGenRenderbuffers(1, &rbo6);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo6);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo6); // now actually attach it
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// ---------------------/FakeLights--------------
		//--------------------ThresholdBuffer------------
		glGenFramebuffers(1, &thresholdBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, thresholdBuffer);
		// create a color attachment texture
		glGenTextures(1, &thresholdTextureBuffer);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, thresholdTextureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, thresholdTextureBuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo7;
		glGenRenderbuffers(1, &rbo7);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo7);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo7); // now actually attach it
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//--------------------BlurShader-----------
		glGenFramebuffers(1, &featureGenerationBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, featureGenerationBuffer);
		// create a color attachment texture
		glGenTextures(1, &featureGenerationTextureBuffer);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, featureGenerationTextureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, featureGenerationTextureBuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo9;
		glGenRenderbuffers(1, &rbo9);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo9);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo9); // now actually attach it
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//--------------------/BlurShader----------
		//--------------------BlenderShader---------------
		unsigned int blenderShaderBuffer;
		glGenFramebuffers(1, &blenderShaderBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, blenderShaderBuffer);
		// create a color attachment texture
		unsigned int blenderShaderTextureBuffer;
		glGenTextures(1, &blenderShaderTextureBuffer);
		glBindTexture(GL_TEXTURE_2D, blenderShaderTextureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blenderShaderTextureBuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo10;
		glGenRenderbuffers(1, &rbo10);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo10);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo10); // now actually attach it
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//--------------------/BlenderShader--------------
		//--------------------LensFlareShader---------------
		glGenFramebuffers(1, &lensFlareShaderBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, lensFlareShaderBuffer);
		// create a color attachment texture
		glGenTextures(1, &lensFlareShaderTextureBuffer);
		glBindTexture(GL_TEXTURE_2D, lensFlareShaderTextureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, lensFlareShaderTextureBuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo11;
		glGenRenderbuffers(1, &rbo11);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo11);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo11); // now actually attach it
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//--------------------/LensFlareShader--------------
		//--------------------FinalShader---------------
		unsigned int finalShaderBuffer;
		glGenFramebuffers(1, &finalShaderBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, finalShaderBuffer);
		// create a color attachment texture
		unsigned int finalShaderTextureBuffer;
		glGenTextures(1, &finalShaderTextureBuffer);
		glBindTexture(GL_TEXTURE_2D, finalShaderTextureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, finalShaderTextureBuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo12;
		glGenRenderbuffers(1, &rbo12);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo12);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo12); // now actually attach it
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//--------------------/FinalShader--------------

		float screenVertices[] = {
			// positions        // texture coords
			-1.0, -1.0, 0.0,	0.0, 1.0,
			1.0, -1.0, 0.0,    1.0, 1.0,
			1.0,  1.0, 0.0,    1.0, 0.0,
			-1.0,  1.0, 0.0,    0.0, 0.0
		};

		unsigned int screenIndices[] = {
			0, 1, 2, // first triangle
			2, 3, 0  // second triangle
		};

		glGenVertexArrays(1, &screenVao);
		glBindVertexArray(screenVao);

		unsigned int screenBuffer;
		glGenBuffers(1, &screenBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, screenBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), screenVertices, GL_STATIC_DRAW);

		unsigned int screenEBO;
		glGenBuffers(1, &screenEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screenEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(screenIndices), screenIndices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void draw(Camera* camera, glm::vec3 lightPos)
	{
		/*bool lensflare = true;
		bool dof = false;
		bool motionblur = false;*/
		//----------------Pass 3--------------
		glBindFramebuffer(GL_FRAMEBUFFER, fakeLightsBuffer); //fakeLightsBuffer
		glClear(GL_COLOR_BUFFER_BIT);

		plainShaders.use();
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(screenVao);

		plainShaders.setFloat("aspect", 1);
		glm::vec3 toLight = glm::normalize(lightPos - camera->Position);
		plainShaders.setFloat("offsetX", fmax(fmin(1.0, (1 + glm::dot(toLight, camera->Right)) / 2), 0.0));
		plainShaders.setFloat("offsetY", fmax(fmin(1.0, (1 + glm::dot(toLight, camera->Up)) / 2), 0.0));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		GLCheckError();

		//-----------------Pass 4--------------------------------------------
		glBindFramebuffer(GL_FRAMEBUFFER, thresholdBuffer); //thresholdBuffer
		glClear(GL_COLOR_BUFFER_BIT);

		thresholdShaders.use();
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(screenVao);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, fakeLightsTextureBuffer);
		thresholdShaders.setInt("tDiffuse", 3);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 4);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		GLCheckError();

		//-----------------------------------------

		//-----------------Pass 5--------------------------------------------
	    glBindFramebuffer(GL_FRAMEBUFFER, featureGenerationBuffer); //blurBuffer
		glClear(GL_COLOR_BUFFER_BIT);

		featureGenerationShaders.use();
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(screenVao);

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, thresholdTextureBuffer);//thresholdTextureBuffer
		featureGenerationShaders.setInt("tDiffuse", 4);

		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, lenscolor);
		featureGenerationShaders.setInt("tLensColor", 5);

		featureGenerationShaders.setFloat("uGhostDispersal", 0.35f);
		featureGenerationShaders.setFloat("uDistortion", 4.5f);
		featureGenerationShaders.setFloat("uHaloWidth", 0.25f);
		featureGenerationShaders.setFloat("screenWidth", SCR_HEIGHT / 2);
		featureGenerationShaders.setFloat("screenHeight", SCR_WIDTH / 2);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 4);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		GLCheckError();
		//-----------------------------------------

		//-----------------Pass 7--------------------------------------------
		//glBindFramebuffer(GL_FRAMEBUFFER, lensFlareShaderBuffer);//lensFlareShaderBuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);//lensFlareShaderBuffer
		//glClear(GL_COLOR_BUFFER_BIT);

		blendShader.use();
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(screenVao);

		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, featureGenerationTextureBuffer);
		blendShader.setInt("tDiffuse", 7);

		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, lensdirt);
		blendShader.setInt("tLensDirt", 8);

		glActiveTexture(GL_TEXTURE9);
		glBindTexture(GL_TEXTURE_2D, lenscolor);
		blendShader.setInt("tLensColor", 9);

		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, lensstar);
		blendShader.setInt("tLensStar", 10);

		//blendShader.setFloat("mixRatio", 0.5f);
		blendShader.setFloat("mixRatio", 0.5f);
		blendShader.setFloat("artefactScale", 0.0f);
		blendShader.setFloat("opacity", 2.0f);

		glm::mat4 lensStarMatrix = glm::mat4(1.0);
		float angle = ((camera->Yaw + camera->Pitch) * 0.5)*(M_PI / 180);
		glm::mat4 scaleBias1 = glm::translate(lensStarMatrix, glm::vec3(-0.5, -0.5, 0.0));
		glm::mat4 rotation = glm::rotate(lensStarMatrix, angle, glm::vec3(0, 0, 1));
		glm::mat4 scaleBias2 = glm::translate(lensStarMatrix, glm::vec3(0.5, 0.5, 0.0));
		lensStarMatrix = scaleBias2 * rotation * scaleBias1;
		int tLensStarMatrix = glGetUniformLocation(blendShader.ID, "tLensStarMatrix");
		glUniformMatrix4fv(tLensStarMatrix, 1, GL_FALSE, glm::value_ptr(lensStarMatrix));

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 4);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		GLCheckError();
		//-----------------------------------------
		////-----------------Pass 8--------------------------------------------
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glClear(GL_COLOR_BUFFER_BIT);

		//finalShader.use();
		//glDisable(GL_DEPTH_TEST);
		//glBindVertexArray(screenVao);

		//glActiveTexture(GL_TEXTURE11);
		//glBindTexture(GL_TEXTURE_2D, screenTexture);
		//finalShader.setInt("tMotionBlur", 11);

		//glActiveTexture(GL_TEXTURE12);
		//glBindTexture(GL_TEXTURE_2D, lensFlareShaderTextureBuffer); //lensFlareShaderTextureBuffer
		//finalShader.setInt("tLensFlare", 12);

		//finalShader.setFloat("mixRatio", 0.4);

		//glGenerateMipmap(GL_TEXTURE_2D);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 4);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
		//GLCheckError();
		glEnable(GL_DEPTH_TEST);
		//-----------------------------------------
	}
};