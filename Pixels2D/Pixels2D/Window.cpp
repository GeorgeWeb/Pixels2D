#include "Window.h"
#include "Errors.h"

#include <SDL/SDL_image.h>

#include <iostream>

using namespace Pixels2D;

Window::Window()
{
}

Window::~Window()
{
}

const int &Window::create(const std::string &windowTitle, const unsigned int &screenWidth, const unsigned int &screenHeight, const unsigned int &currentFlags)
{
	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE)
		flags |= SDL_WINDOW_HIDDEN;
	if (currentFlags & FULLSCREEN)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (currentFlags & BORDERLESS)
		flags |= SDL_WINDOW_BORDERLESS;

	// create a window
	_sdlWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
	// check for window errors
	if (_sdlWindow == nullptr)
		Errors::fatalError("SDL Window could not be created!");

	// create icon
	SDL_Surface *surface = IMG_Load("Icon/game.ico");
	// attach the icon to the window pointer
	SDL_SetWindowIcon(_sdlWindow, surface);

	// store the SDL_GL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
	// check for SDL_GL context errors
	if (glContext == nullptr)
		Errors::fatalError("SDL_GL context could not be created!");

	// initialize glew
	GLenum glew = glewInit();
	// check for initialization errors
	if (glew != GLEW_OK)
		Errors::fatalError("Could not initialize glew!");

	std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

	// set the background color
	// some nice blue: (0, 0.74902, 1, 1)
	glClearColor(0.03529, 0.29020, 0.69804, 1);

	// set VSYNC
	SDL_GL_SetSwapInterval(1);
	
	// enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void Window::swapBuffer()
{
	// swap the buffer and drawn everything to the screen
	SDL_GL_SwapWindow(_sdlWindow);
}