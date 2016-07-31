#ifndef MAINGAME_HGUARD
#define MAINGAME_HGUARD

#include <Pixels2D/Window.h>
#include <Pixels2D/GLSLProgram.h>
#include <Pixels2D/Camera2D.h>
#include <Pixels2D/InputManager.h>

enum class GameState
{
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	// runs the game
	void run();

private:
	// initializes the core systems
	void initSystems();

	// initializes the shaders
	void initShaders();

	// main game loop for the program
	void gameLoop();

	// handles input processing
	void processInput();

	// renders the game
	void drawGame();

private:
	// the game window
	Pixels2D::Window _window;

	// the shader program
	Pixels2D::GLSLProgram _textureProgram;

	// handles input
	Pixels2D::InputManager _inputManager;

	// main camera
	Pixels2D::Camera2D _camera;

	// window dimensions
	unsigned int _screenWidth, _screenHeight;

	// stores and controls the game state
	GameState _gameState;
};

#endif // !MAINGAME_HGUARD