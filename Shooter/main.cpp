#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../GameStates/Game.h"
#include <filesystem>
#include <glm/glm.hpp>

class CmdHandler
{
	Settings s
	{
		{ 1280, 720 }
	};

public:

	Settings& getSettings() { return s; }

	void handle(int& argc, char** argv)
	{
		std::filesystem::path p("settings.cfg");

		if (std::filesystem::exists(p))
		{
			std::ifstream settingsFile("settings.cfg", std::ios::binary);
			settingsFile.read((char*) &s.res.x, sizeof s.res.x);
			settingsFile.read((char*) &s.res.y, sizeof s.res.y);
		}
		else
		{
			std::ofstream settingsFile("settings.cfg", std::ios::binary | std::ios::trunc);
			settingsFile.write((char*) &s.res.x, sizeof s.res.x);
			settingsFile.write((char*) &s.res.y, sizeof s.res.y);
		}

		for (int i = 1; i < argc; ++i)
		{
			if ((!strcmp(argv[i], "-r") || !strcmp(argv[i], "--resolution")) && i + 2 < argc)
			{
				s.res = { std::stoi(argv[i + 1]), std::stoi(argv[i + 2]) };
				i += 2; continue;
			}

		}
	}
};

/* Could take resolution as cmd line argument */
int main(int argc, char** argv)
{
	CmdHandler c;

	c.handle(argc, argv);

	Game g(c.getSettings());
	return g.run();
}