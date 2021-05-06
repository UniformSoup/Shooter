#pragma once

#include <stb_image.h>
#include <glad/glad.h>

#include <string>
#include <exception>
#include <stdexcept>

class Texture
{
	GLuint ID;
public:
	Texture(const std::string& filename)
		: ID(NULL)
	{
		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		unsigned char* img = (unsigned char*) stbi_load(filename.c_str(), &width, &height, &channels, STBI_default);

		if (img == NULL)
			std::throw_with_nested(std::runtime_error("Could not read: " + filename));

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenerateMipmap(GL_TEXTURE_2D);
		
		GLenum format;
		switch (channels)
		{
		case STBI_rgb:
			format = GL_RGB;
			break;
		case STBI_rgb_alpha:
			format = GL_RGBA;
			break;
		/*case STBI_grey:
			format = GL_LUMINANCE;
			break;
		case STBI_grey_alpha:
			format = GL_LUMINANCE_ALPHA;
			break;*/
		default:
			std::throw_with_nested(std::runtime_error("Unknown image format for: " + filename));
			break;
		}

		/* Could change so internal image is compressed */
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, img);

		stbi_image_free(img);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	~Texture() { glDeleteTextures(1, &ID); }
	GLint getID() const { return ID; }
	void bind() const { glBindTexture(GL_TEXTURE_2D, ID); }
};