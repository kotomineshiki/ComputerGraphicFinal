#include "Text.h"

using namespace std;

void Text::LoadText(Shader &shader, GLuint width, GLuint height) {
	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader.use();
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));
	shader.setMat4("projection", projection);

	// FreeType
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, "resources/fonts/Arial.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 80);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 255; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDisable(GL_CULL_FACE);

}

void Text::RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// Activate corresponding render state	
	shader.use();
	shader.setVec3("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
		{ xpos,     ypos,       0.0, 1.0 },
		{ xpos + w, ypos,       1.0, 1.0 },

		{ xpos,     ypos + h,   0.0, 0.0 },
		{ xpos + w, ypos,       1.0, 1.0 },
		{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::DrawHint(Shader shaderText) {
	RenderText(shaderText, "Press E to interact with this object", 130.0f, 100.0f, 0.5f, glm::vec3(0.8f, 0.7f, 0.0f));
}

void Text::drawHome(Shader shaderText, float screenwith, float screenheight) {
	RenderText(shaderText, "The  Broloc", (screenwith / 2.0f) - 180, screenheight / 2.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "Press space to start", (screenwith / 2.0f) - 100, (screenheight / 2.0f) - 70, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Text::drawCommand(Shader shaderText) {
	RenderText(shaderText, "Commands :", 300.0f, 600.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "zqsd or arrow keys :", 400.0f, 500.0f, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "Move", 700.0f, 500.0f, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "space :", 400.0f, 450.0f, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "Pass the text", 700.0f, 450.0f, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "e :", 400.0f, 400.0f, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "Interact with object", 700.0f, 400.0f, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "esc :", 400.0f, 350.0f, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "Quit", 700.0f, 350.0f, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
}

//void Text::drawEnd1(Shader shaderText, float screenwith, float screenheight) {
//	RenderText(shaderText, "Who killed Guilhem ?!", (screenwith / 2.0f) - 300, screenheight / 2.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//	RenderText(shaderText, "Press space to try again", (screenwith / 2.0f) - 100, (screenheight / 2.0f) - 70, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
//}

void Text::drawEnd1(Shader shaderText, float screenwith, float screenheight) {
	RenderText(shaderText, "Who killed Guilhem ?!", 30, 30, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "Press space to try again", (screenwith / 2.0f) - 100, (screenheight / 2.0f) - 70, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Text::drawEnd2(Shader shaderText, float screenwith, float screenheight) {
	RenderText(shaderText, "I killed him...", (screenwith / 2.0f) - 180, screenheight / 2.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(shaderText, "Press space to try again", (screenwith / 2.0f) - 100, (screenheight / 2.0f) - 70, 0.3f, glm::vec3(1.0f, 1.0f, 1.0f));
}