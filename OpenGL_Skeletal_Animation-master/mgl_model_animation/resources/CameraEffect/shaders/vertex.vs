#version 330 core

out vec2 vTexCoord;

layout(location = 0) in vec4 position;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 uTransform;

vec4 vDofParams = vec4(3.0, 5.0, 7.0, 1.0);

float ComputeDepthBlur(float depth){
	float f;
	if(depth < vDofParams.y) {
		f = (depth - vDofParams.y)/(vDofParams.y - vDofParams.x);
	}else {
		f = (depth - vDofParams.y)/(vDofParams.z - vDofParams.y);
		f = clamp(f, 0, vDofParams.w);
	}
	return f * 0.5f + 0.5f;
}

void main() 
{ 
	vTexCoord = aTexCoord;
	gl_Position = projection * view * model * uTransform * position;
}