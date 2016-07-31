#ifndef CAMERA2D_HGUARD
#define CAMERA2D_HGUARD

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::ortho

namespace Pixels2D
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(const unsigned &screenWidth, const unsigned int &screenHeight);
	
		void update();

		const glm::vec2 &convertScreenToWorld(glm::vec2 screenCoords);

		// setters
		inline void setPosition(const glm::vec2 &newPosition) {
			_position = newPosition;
			_needsMatrixUpdate = true;
		}
		inline void setScale(const float &newScale) {
			_scale = newScale;
			_needsMatrixUpdate = true;
		}

		// getters
		inline const glm::vec2 &getPosition() { return _position; }
		inline const float &getScale() { return _scale; }
		inline const glm::mat4 &getCameraMatrix() { return _cameraMatrix; }

	private:
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		float _scale;
		bool _needsMatrixUpdate;

		unsigned int _screenWidth, _screenHeight;
	};
}

#endif // !CAMERA2D_HGUARD