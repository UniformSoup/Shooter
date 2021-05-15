#include <glad/glad.c>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../GameStates/Game.h"

int main()
{	
	Game g("Lesss Goooo", 1080, 720);
	return g.run();
}