#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>

#include <GL/glew.h>

class Texture
{
public:
	Texture(GLenum TextureTarget, const std::string& FileName);

	bool Load();

	void Bind(GLenum TextureUnit);

private:
	std::string m_fileName;
	GLenum m_textureTarget;
	GLuint m_textureObj;
	unsigned char * m_blob;
};


#endif	/* TEXTURE_H */

#pragma once
