#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 TexCoord;

// texture samplers
uniform sampler2D ourTexture;

void main()
{
	FragColor = vec4(color,1.0f) * texture(ourTexture, TexCoord);
}