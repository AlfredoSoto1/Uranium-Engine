#pragma once

#include <memory>
#include "Camera.h"

namespace Uranium::Scenes::Cameras {

	/*
	* Blueprint of First person camera
	*/
	class FPCamera : public Camera {
	public:
		/*
		* Custom alias
		*/

	public:
		FPCamera();
		virtual ~FPCamera();

		void update();

	private:
		/*
		* private methods
		*/
		void calcCameraRotation();
		void calcMovementDirection();

		float getDirectionFromKey(int key1, int key2);

	private:
		/*
		* private members
		*/
		double timeFactor;
		double responceTime;

		double xSensitivity;
		double ySensitivity;

		double xTraslation;
		double yTraslation;

		float cameraSpeed;

		bool grabOnCommand;
	
	};
}