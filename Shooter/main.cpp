#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../GameStates/Game.h"

/* Could take resolution as cmd line argument */
int main()
{	
	Game g(1080, 720);
	return g.run();
}