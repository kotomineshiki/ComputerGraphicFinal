//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stb_image.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <learnopengl/filesystem.h>
//#include <learnopengl/shader.h>
//#include <learnopengl/camera.h>
//#include <learnopengl/model.h>
//
//#include <iostream>
//class Shadow {
//public:
//	Shader shader;
//	Shader simpleDepthShader;
//	Shader debugDepthQuad;
//	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
//	glm::mat4 lightProjection, lightView;
//	glm::mat4 lightSpaceMatrix;
//	glm::vec3 lightPos;
//	unsigned int woodTexture;
//	unsigned int depthMapFBO;
//	unsigned int depthMap;
//	Shadow() :shader("shadow_mapping.vs", "shadow_mapping.fs"),
//		simpleDepthShader("shadow_mapping_depth.vs", "shadow_mapping_depth.fs"),
//		debugDepthQuad("debug_quad.vs", "debug_quad_depth.fs"),
//		lightPos(-4.0f, 4.0f, -1.0f) {
//
//		// configure depth map FBO
//
//
//		glGenFramebuffers(1, &depthMapFBO);
//		// create depth texture
//
//		glGenTextures(1, &depthMap);
//		glBindTexture(GL_TEXTURE_2D, depthMap);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
//		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//		// attach depth texture as FBO's depth buffer
//		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
//		glDrawBuffer(GL_NONE);
//		glReadBuffer(GL_NONE);
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		// shader configuration
//
//		shader.use();
//		shader.setInt("diffuseTexture", 0);
//		shader.setInt("shadowMap", 1);
//		debugDepthQuad.use();
//		debugDepthQuad.setInt("depthMap", 0);
//	}
//	void SetLightPosition(glm::vec3 input) {
//		lightPos = input;
//	}
//	void SetLightProjection(glm::mat4 input) {
//		lightProjection = input;
//	}
//	void Step1() {
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		// 1. render depth of scene to texture (from light's perspective)
//// --------------------------------------------------------------
//
//		float near_plane = 1.0f, far_plane = 7.5f;
//		SetLightProjection(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane));
//		// note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
//	   //
//		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
//		lightSpaceMatrix = lightProjection * lightView;
//		// render scene from light's point of view
//		simpleDepthShader.use();
//		simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
//
//		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
//		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//		glClear(GL_DEPTH_BUFFER_BIT);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, woodTexture);
//		renderScene(simpleDepthShader);
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	}
//	void Step2() {
//		// reset viewport
//		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		shader.use();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//		// set light uniforms
//		shader.setVec3("viewPos", camera.Position);
//		shader.setVec3("lightPos", lightPos);
//		shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, woodTexture);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, depthMap);
//	}
//	void Run() {
//		Step1();
//		Step2();
//	}
//	void SetTexture(unsigned int input) {
//		woodTexture = input;
//	}
//};