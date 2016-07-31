#include "InputManager.h"

using namespace Pixels2D;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::pressKey(const unsigned int &keyID)
{
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(const unsigned int &keyID)
{
	_keyMap[keyID] = false;
}


bool InputManager::isKeyPressed(const unsigned int &keyID)
{
	auto umit = _keyMap.find(keyID);
	if (umit != _keyMap.end())
		return _keyMap[keyID];
	else
		return false;
}

void InputManager::setMouseCoords(const float &x, const float &y)
{
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}
