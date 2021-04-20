#include <glad/glad.c>
#include "Game.h"

inline void pause() { std::cout << "Press Enter to continue...\n"; std::cin.get(); }

int main()
{	
	Game g("Lesss Goooo", 1080, 720);
	return g.run();
}