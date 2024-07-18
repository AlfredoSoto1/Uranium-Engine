#pragma once

#include "Core/Math/vec3.h"
#include "Core/Math/mat4.h"

namespace Uranium::Scenes::Cameras {

	/*
	* Blueprint of Abstract class - Camera
	* This contains the basics of what a camera
	* needs such as:
	*  + position
	*  + rotation
	*  + direction
	*  + transformation matrices
	*  + ... and more
	*/
	class Camera {
	public:
		/*
		* public alias
		*/
		using vec3 = Core::Math::vec3;
		using mat4 = Core::Math::mat4;

	public:
		Camera();
		virtual ~Camera();

	public:
		/*
		* Getter references:
		* 
		* These return a reference to the corresponding
		* private member of 'this' instance
		*/

		mat4& getViewMatrix();
		mat4& getProjectionMatrix();

		vec3& getPosition();
		vec3& getRotation();

	public:
		/*
		* Copy setters :
		* 
		* Copies whatever the target value has as
		* a parameter to 'this' current private members
		*/

		void setViewMatrix(const mat4& viewMat);
		void setProjectionMatrix(const mat4& projMat);

		void setPosition(const vec3& position);
		void setRotation(const vec3& rotation);

	protected:
		/*
		* protected members
		*/
		vec3 position;
		vec3 rotation;
		vec3 direction;

		mat4 viewMatrix;
		mat4 projectionMatrix;

		double fov;
		double nearPlane;
		double farPlane;

		double xSensitivity;
		double ySensitivity;

	private:
		/*
		* private members
		*/
		bool isLocked;

	};
}