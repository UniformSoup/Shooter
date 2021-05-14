#version 430 core
precision highp float;

in vec2 texcoords;

uniform sampler2D tex;
uniform bool flip = false;
uniform float t = 0.0f;

out vec4 FragColor;

void main()
{
	FragColor = texture(tex, texcoords);

	if (flip) FragColor *= vec4(0.5f, 0.5f, 0.5f, 0.f) + vec4(0.5f * sin(t), 0.5f * cos(t), 0.5f * sin(t) * cos(t), 1.f);

	//FragColor = vec4(sin(t + gl_FragCoord.x / 1080.f), cos(t + gl_FragCoord.y / 720.f), sin(t + gl_FragCoord.x / 1080.f) * cos(t + gl_FragCoord.y / 720.f), 1.f) / ;
	//FragColor = texture(tex, texcoords) * vec4(sin(t + gl_FragCoord.x / 1080.f), cos(t + gl_FragCoord.y / 720.f), sin(t + gl_FragCoord.x / 1080.f) * cos(t + gl_FragCoord.y / 720.f), 1.f);
}