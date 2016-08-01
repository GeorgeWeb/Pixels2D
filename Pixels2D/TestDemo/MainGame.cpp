#include "MainGame.h"

#include <Pixels2D/Pixels2D.h>
#include <Pixels2D/ResourceManager.h>
#include <Pixels2D/GLTexture.h>

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
	
	/* initialize _spriteBatch to render */
	_spriteBatch.init();
	_spriteBatch.begin();

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

   // zoom out the camera by 2x
	const float CAMERA_SCALE = 1.0f / 2.0f;
	_camera.setScale(CAMERA_SCALE);

   // main loop
	while (_gameState == GameState::PLAY)
	{
		// keyboard/mouse input handling
		processInput();

		// set camera position
		_camera.setPosition(glm::vec2(_screenWidth, _screenHeight));

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

	_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);

	// make sure the shader uses texture 0
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// get the (projection) camera matrix 
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &cameraMatrix[0][0]);

	/* initialize texture data => */
	// set uv rect
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	// set color
	Pixels2D::ColorRGBA8 color(255, 255, 255, 255);
	// set dest rect
	glm::vec4 destRect(0, 0, 1650, 1200);
	// set texture
	static Pixels2D::GLTexture texture = Pixels2D::ResourceManager::getTexture("Textures/light_bricks.png");
	// set depth
	float depth = 0.0f;

	/* draw texture => */
	_spriteBatch.draw(destRect, uvRect, texture.id, depth, color);

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	
	_textureProgram.unuse();
   
    // swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}