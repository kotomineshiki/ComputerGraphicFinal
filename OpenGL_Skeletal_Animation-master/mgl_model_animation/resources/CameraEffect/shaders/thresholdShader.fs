#version 330 core
uniform sampler2D tDiffuse;

in vec2 vTexCoord;
out vec4 color;

void main(){
	vec4 uScale = vec4(10, 10, 10, 1);
	vec4 uBias = vec4(-0.9, -0.9, -0.9, 0);
	vec4 texColor = texture(tDiffuse, vTexCoord);
	if (texColor.r < 0.1 && texColor.g < 0.1 && texColor.b < 0.1)
		discard;
	color = max(vec4(0.0), texColor + uBias) * uScale;
}