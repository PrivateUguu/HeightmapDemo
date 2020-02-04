#version 330 core

in vec3 vPos;
in vec3 vColor;
in mat4 instanceMatrix;

out vec4 color;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * instanceMatrix * vec4(vPos, 1.0f);
	color = vec4(vColor, 1.0f);
}