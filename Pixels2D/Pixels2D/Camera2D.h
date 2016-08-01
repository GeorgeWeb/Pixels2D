#pragma once

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

		bool isBoxInView(const glm::vec2 &position, const glm::vec2 &dimensions);

		// setters
		inline void setPosition(const glm::vec2 &newPosition) {
			m_position = newPosition;
			m_needsMatrixUpdate = true;
		}
		inline void setScale(const float &newScale) {
			m_scale = newScale;
			m_needsMatrixUpdate = true;
		}

		// getters
		inline const glm::vec2 &getPosition() { return m_position; }
		inline const float &getScale() { return m_scale; }
		inline const glm::mat4 &getCameraMatrix() { return m_cameraMatrix; }

	private:
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;
		float m_scale;
		bool m_needsMatrixUpdate;

		unsigned int m_screenWidth, m_screenHeight;
	};
}

#endif // !CAMERA2D_HGUARD