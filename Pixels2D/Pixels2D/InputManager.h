#ifndef INPUTMANAGER_HGUARD
#define INPUTMANAGER_HGUARD

#include <unordered_map>
#include <glm/glm.hpp>

namespace Pixels2D
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(const unsigned int &keyID);
		void releaseKey(const unsigned int &keyID);

		// returns true if key is is held down
		bool isKeyDown(const unsigned int &keyID);

		// returns true if key was just pressed
		bool isKeyPressed(const unsigned int &keyID);

		// setters
		void setMouseCoords(const float &x, const float &y);

		// getters
		inline const glm::vec2 &getMouseCoords() const { return m_mouseCoords; }

	private:
		bool wasKeyDown(const unsigned int &keyID);

	private:
		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;
		glm::vec2 m_mouseCoords;
	};
}

#endif // !INPUTMANAGER_HGUARD