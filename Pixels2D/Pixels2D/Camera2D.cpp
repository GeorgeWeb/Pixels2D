#include "Camera2D.h"

using namespace Pixels2D;

Camera2D::Camera2D() : _position(0.0f, 0.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f), _scale(1.0f), _needsMatrixUpdate(true), _screenWidth(500), _screenHeight(500)
{}


Camera2D::~Camera2D()
{
}

void Camera2D::init(const unsigned &screenWidth, const unsigned int &screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, float(_screenHeight));
}

void Camera2D::update()
{
	if (_needsMatrixUpdate)
	{
		// camera translation
		glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);

		// camera scale
		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

		_needsMatrixUpdate = false;
	}
}

const glm::vec2 &Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
{
	// invert Y direction
	screenCoords.y = _screenHeight - screenCoords.y;
	// make 0 the center
	screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
	// scale the coordinates
	screenCoords /= _scale;
	// translate the camera position
	screenCoords += _position;

	return screenCoords;
}

bool Camera2D::isBoxInView(const glm::vec2 &position, const glm::vec2 &dimensions)
{
	glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / _scale;

	// minimum distance before a collision occures
	const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
	const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

	// center position of the parameters
	glm::vec2 centerPosition = _position + dimensions / 2.0f;
	// center position of the camera
	glm::vec2 centerCameraPosition = _position;
	glm::vec2 distVec = centerPosition - centerCameraPosition;

	// get the depth of collision
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	// if this is ture then we collide
	if (xDepth > 0 || yDepth > 0)
		return true;

	return false;
}