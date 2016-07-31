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

		void pressKey(const unsigned int &keyID);
		void releaseKey(const unsigned int &keyID);
		bool isKeyPressed(const unsigned int &keyID);

		// setters
		void setMouseCoords(const float &x, const float &y);

		// getters
		inline const glm::vec2 &getMouseCoords() const { return _mouseCoords; }

	private:
		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;
	};
}

#endif // !INPUTMANAGER_HGUARD