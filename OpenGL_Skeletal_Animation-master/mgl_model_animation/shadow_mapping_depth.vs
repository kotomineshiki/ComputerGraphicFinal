#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;
uniform float time;
void main()
{
	vec3 currentPos=aPos;
//	currentPos.y=3.0*cos(currentPos.x-1*time);
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}