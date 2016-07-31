#ifndef WINDOW_HGUARD
#define WINDOW_HGUARD

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace Pixels2D
{
	enum WindowFlags
	{
		INVISIBLE = 0x1,	// 1st bit
		FULLSCREEN = 0x2,	// 2nd bit
		BORDERLESS = 0x4		// 3rd bit
	};

	class Window
	{
	public:
		Window();
		~Window();

		const int &create(const std::string &windowTitle, const unsigned int &screenWidth, const unsigned int &screenHeight, const unsigned int &currentFlags);
		inline const int &getScreenWidth() { return _screenWidth; }
		inline const int &getScreenHeight() { return _screenHeight; }

		void swapBuffer();

	private:
		SDL_Window *_sdlWindow;
		unsigned int _screenWidth, _screenHeight;
	};

}

#endif // !WINDOW_HGUARD