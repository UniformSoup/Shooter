#version 330 core
precision highp float;
uniform float t;

out vec4 FragColor;

void main()
{
	FragColor = vec4(sin(t + gl_FragCoord.x/1080.f), cos(t + gl_FragCoord.y/720.f), sin(t + gl_FragCoord.x / 1080.f) * cos(t + gl_FragCoord.y / 720.f), 1.0);
}