#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 model;
uniform mat4 projection;
uniform vec3 spriteColor;

out vec3 color;
out vec2 TexCoord;

void main()
{
	gl_Position = projection * model * vec4(aPos, 1.0);
	color = spriteColor * aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}