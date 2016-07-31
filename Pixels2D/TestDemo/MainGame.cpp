#include "MainGame.h"

#include <Pixels2D/Pixels2D.h>

#include <SDL/SDL.h>
#include <iostream>

MainGame::MainGame() :_screenWidth(800), _screenHeight(600), _gameState(GameState::PLAY)
{}

MainGame::~MainGame() {
    // IMPLEMENT THIS!
}

void MainGame::run() {
    // IMPLEMENT THIS!
	
	// call the initialized systems
	initSystems();
	
	// call the main game loop
	gameLoop();
}

void MainGame::initSystems() {
    // IMPLEMENT THIS!

	// initialize the game engine
	Pixels2D::init();

	// create the window
	_window.create("Pixels2D - Game Engine", _screenWidth, _screenHeight, 0);

	// set background color
	glClearColor(0.17255, 0.27059, 0.40000, 0);

	// set up the shaders
	initShaders();

	// set up the camera
	_camera.init(_screenWidth, _screenHeight);
}

void MainGame::initShaders()
{
    // compile the color shader(s)
    _textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
    _textureProgram.linkShaders();
}

void MainGame::gameLoop()
{	
   // IMPLEMENT THIS!

   // main loop
	while (_gameState == GameState::PLAY)
	{
		// keyboard/mouse input handling
		processInput();

		// updates the main camera
		_camera.update();

		// draws the game window and objects, etc.
		drawGame();
	}
}

void MainGame::processInput()
{
    SDL_Event evnt;
    
	// will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt))
	{
        switch (evnt.type)
		{
            case SDL_QUIT:
                // exit the game here
				_gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _inputManager.releaseKey(evnt.button.button);
                break;
        }
    }
}

void MainGame::drawGame()
{
    // set the base depth to 1.0
    glClearDepth(1.0);
    // clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // IMPLEMENT THIS!
   
    // swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}