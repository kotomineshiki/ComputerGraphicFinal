#pragma once 

#include <glm/glm.hpp>
// #include <glad/glad.h>
#include <GL/glew.h>
#include"shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

class Text {

public:

	void LoadText(Shader &shader, GLuint width, GLuint height);
	void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	void DrawHint(Shader shaderText);
	void drawHome(Shader shaderText, float screenwith, float screenheight);
	void drawCommand(Shader shaderText);
	void drawEnd1(Shader shaderText, float screenwith, float screenheight);
	void drawEnd2(Shader shaderText, float screenwith, float screenheight);
	void drawSample(Shader shaderText, float screenwith, float screenheight);
private:

	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

	std::map<GLchar, Text::Character> Characters;
	GLuint VAO, VBO;


};
