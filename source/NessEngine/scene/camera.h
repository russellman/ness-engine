/**
* A camera you can use to "navigate" in scenes
* Author: Ronen Ness
* Since: 07/1014
*/

#pragma once
#include "../exports.h"
#include "../basic_types/point.h"
#include "../basic_types/containers.h"

namespace Ness
{
	/**
	* Cameras are objects you can create and render scenes with, and they will move all entities in the scene to fit camera position.
	* this is your method to "navigate" in a larger node without actually moving entities but rather move the camera instead.
	*/
	class Camera
	{
	public:
		Point position;

		NESSENGINE_API Camera(const Point& Position) : position(Position) {}
		NESSENGINE_API Camera() : position(0, 0) {}

		// some useful operators
		NESSENGINE_API void operator*=(float scalar) {position *= scalar;}
		NESSENGINE_API void operator/=(float scalar) {position /= scalar;}
		NESSENGINE_API void operator-=(float scalar) {position -= scalar;}
		NESSENGINE_API void operator+=(float scalar) {position += scalar;}
		NESSENGINE_API void operator*=(const Point& pos) {position *= pos;}
		NESSENGINE_API void operator/=(const Point& pos) {position /= pos;}
		NESSENGINE_API void operator-=(const Point& pos) {position -= pos;}
		NESSENGINE_API void operator+=(const Point& pos) {position += pos;}
		NESSENGINE_API void operator*=(const Camera& other) {position *= other.position;}
		NESSENGINE_API void operator/=(const Camera& other) {position /= other.position;}
		NESSENGINE_API void operator-=(const Camera& other) {position -= other.position;}
		NESSENGINE_API void operator+=(const Camera& other) {position += other.position;}
	};

	// camera pointer
	NESSENGINE_API typedef SharedPtr<Camera> CameraPtr;

	// null camera
	#define NullCamera CameraPtr()
};