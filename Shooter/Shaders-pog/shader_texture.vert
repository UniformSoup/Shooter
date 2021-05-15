#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texco;
uniform mat4 model = mat4(1.f), view, projection;

out vec2 texcoords;

void main()
{
	texcoords = texco;
	gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
}