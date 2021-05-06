#version 330 core
precision highp float;

in vec2 texcoords;

uniform sampler2D tex;
out vec4 FragColor;

void main()
{
	FragColor = texture(tex, texcoords);
	//FragColor = vec4(sin(t + gl_FragCoord.x / 1080.f), cos(t + gl_FragCoord.y / 720.f), sin(t + gl_FragCoord.x / 1080.f) * cos(t + gl_FragCoord.y / 720.f), 1.f);
}