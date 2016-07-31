#include "InputManager.h"

using namespace Pixels2D;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::update()
{
	// loop through a _keyMap and copy it to _previousKeyMap
	for (auto &key : _keyMap)
		_previousKeyMap[key.first] = key.second;
}

void InputManager::pressKey(const unsigned int &keyID)
{
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(const unsigned int &keyID)
{
	_keyMap[keyID] = false;
}


bool InputManager::isKeyDown(const unsigned int &keyID)
{
	auto key = _keyMap.find(keyID);
	if (key != _keyMap.end())
		return key->second;
	else
		return false;
}

bool InputManager::isKeyPressed(const unsigned int &keyID)
{
	// check if the key is pressed this frame, and wasn't pressed last frame
	if (isKeyDown(keyID) && !wasKeyDown(keyID))
		return true;

	return false;
}

void InputManager::setMouseCoords(const float &x, const float &y)
{
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool InputManager::wasKeyDown(const unsigned int &keyID)
{
	auto prevKey = _previousKeyMap.find(keyID);
	if (prevKey != _previousKeyMap.end())
		return prevKey->second;
	else
		return false;
}