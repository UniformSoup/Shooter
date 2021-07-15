#include "Game.h"
#include "MainMenu.h"

#define SHADER_DIR "Shaders/"

std::string getErrorEnumString(const GLenum& err)
{
	switch (err)
	{
	case GL_INVALID_ENUM:					return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:					return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:				return "GL_INVALID_OPERATION";
	case GL_INVALID_FRAMEBUFFER_OPERATION:	return "GL_INVALID_FRAMEBUFFER_OPERATION";
	case GL_OUT_OF_MEMORY:					return "GL_OUT_OF_MEMORY";
	case GL_STACK_UNDERFLOW:				return "GL_STACK_UNDERFLOW";
	case GL_STACK_OVERFLOW:					return "GL_STACK_OVERFLOW";
	default:								return "GL_NO_ERROR";
	}
}

std::string getFboErrorString(const GLenum& status)
{
	switch (status)
	{
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:			return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:	return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:			return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:			return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
	case GL_FRAMEBUFFER_UNSUPPORTED:					return "GL_FRAMEBUFFER_UNSUPPORTED";
	default:											return "GL_FRAMEBUFFER_COMPLETE";
	}
}

void Game::checkForGLErrors()
{
	auto e = glGetError();
	if (e != GL_NO_ERROR)
		throw std::runtime_error("OpenGL Error:\n" + getErrorEnumString(e) + '\n'
			+ getFboErrorString(glCheckFramebufferStatus(GL_FRAMEBUFFER)));
}

Game::Game(const Settings& s)
{
	glfwInit();
	data.win.create((std::string("Shooter Version ") + std::to_string(version.major) + '.' + std::to_string(version.minor)).c_str());

	data.win.setWindowSize(s.res);

	glViewport(0, 0, s.res.x, s.res.y);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int Game::run()
{
	try
	{
		data.shaders.add("basic", std::make_shared<Shader>(SHADER_DIR "shader.vert", SHADER_DIR "shader.frag"));
		data.shaders.add("texture", std::make_shared<Shader>(SHADER_DIR "shader_texture.vert", SHADER_DIR "shader_texture.frag"));
		
		data.win.setMousePos(data.win.getWindowSize() / 2);

		{
			glm::ivec2 size = data.win.getWindowSize();
			glm::mat4 perspective = glm::perspective(glm::radians(75.0f), (size.x / (float) size.y), 0.1f, 200.0f);
			for (auto& s : data.shaders.getResources())
			{
				s.second->use();
				glUniformMatrix4fv(s.second->getUniformLoc("projection"), 1, GL_FALSE, glm::value_ptr(perspective));
			}
		}

		//data.shaders.add("ui", new Shader(SHADER_DIR "ui.vert", "ui.frag"));

		glClearColor(1.f, 0.f, 1.f, 1.f);
		glEnable(GL_DEPTH_TEST);

		stateMachine.addState(std::make_shared<MainMenu>(&data, &stateMachine));

		while (data.win.isOpen())
		{
			stateMachine.updateState();	
			stateMachine.getCurrentState().update(clk());
			stateMachine.getCurrentState().render();
			checkForGLErrors();
		}

		glfwTerminate();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		glfwTerminate();
#ifdef _DEBUG
		std::cerr << e.what() << '\n';
		std::cerr << "Press Enter to continue...\n";
		std::cin.get();
#else
		std::ofstream log("log.txt", std::ifstream::app);
		auto time = std::time(nullptr);
		log << std::put_time(std::localtime(&time), "%F %T\n") << e.what() << "\n\n";
		log.close();
#endif

		return EXIT_FAILURE;
	}
}