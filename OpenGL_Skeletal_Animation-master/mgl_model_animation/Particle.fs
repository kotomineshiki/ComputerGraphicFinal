#version 330 core
in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D particleTexture;

void main()
{
    FragColor = vec4(1.0f,1.0f,1.0f, 1.0f);//texture(particleTexture,TexCoords);
}