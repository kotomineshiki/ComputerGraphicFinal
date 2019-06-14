#version 330 core
in vec2 TexCoords;
uniform vec4 myColor;
out vec4 FragColor;
uniform sampler2D particleTexture;

void main()
{
    FragColor = myColor;//vec4(1.0f,1.0f,1.0f, 1.0f);//texture(particleTexture,TexCoords);
}