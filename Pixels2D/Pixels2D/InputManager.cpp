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
	for (auto &key : m_keyMap)
		m_previousKeyMap[key.first] = key.second;
}

void InputManager::pressKey(const unsigned int &keyID)
{
	m_keyMap[keyID] = true;
}

void InputManager::releaseKey(const unsigned int &keyID)
{
	m_keyMap[keyID] = false;
}


bool InputManager::isKeyDown(const unsigned int &keyID)
{
	auto key = m_keyMap.find(keyID);
	if (key != m_keyMap.end())
		return key->second;
	else
		return false;
}

bool InputManager::isKeyPressed(const unsigned int &keyID)
{
	// check if the key is pressed this frame, and wasn't pressed last frame
	if(isKeyDown(keyID) && !wasKeyDown(keyID))
		return true;

	return false;
}

void InputManager::setMouseCoords(const float &x, const float &y)
{
	m_mouseCoords.x = x;
	m_mouseCoords.y = y;
}

bool InputManager::wasKeyDown(const unsigned int &keyID)
{
	auto prevKey = m_previousKeyMap.find(keyID);
	if (prevKey != m_previousKeyMap.end())
		return prevKey->second;
	else
		return false;
}