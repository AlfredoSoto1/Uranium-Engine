#include <GLFW/glfw3.h>

#include "Core/Application/UraniumApi.h"

#include "Scene.h"
#include "SceneMaster.h"

using namespace Uranium::Scenes;

SceneMaster::SceneMaster()  :
	frameCount(0),

	lastFrame(0),
	lastRefresh(0),
	timeDifference(0),
	lastTimeDifference(0)
{

}

SceneMaster::~SceneMaster() {

}

std::shared_ptr<Scene> SceneMaster::getCurrentScene() {
	return currentScene;
}

volatile double SceneMaster::getTimeInstance() {
	return lastTimeDifference;
}

void SceneMaster::setCurrentScene(std::shared_ptr<Scene> scene) {
	this->currentScene = scene;
}

void SceneMaster::sleepScene(const unsigned int targetTick, const unsigned int triggerTarget, volatile double* lastTick) {

	// if no scene is linked, 
	// skip any process
	if (currentScene == nullptr)
		return;

	//Current thread sleeps here to get to targeted FPS
	if (targetTick == triggerTarget)
		return;

	volatile double timeFraction = 1.0 / targetTick;

	// sleep thread
	while (glfwGetTime() < *lastTick + timeFraction);

	// increase tick by time fraction
	*lastTick += timeFraction;
}

void SceneMaster::render() {

	// if no scene is linked, 
	// skip any process
	if (currentScene == nullptr)
		return;
	
	currentScene->render();
}

void SceneMaster::update() {

	// if no scene is linked, 
	// skip any process
	if (currentScene == nullptr)
		return;

	currentScene->update();

}

void SceneMaster::postUpdate() {

	double currentTime = glfwGetTime();

	// increase frame count
	frameCount++;

	if (currentTime * 1000.0 > lastRefresh + 1000.0) {
		
		// display FPS in console
		print_status("FPS: " << frameCount << ", " << currentTime);
		
		// reset frame count to 0
		frameCount = 0;

		// set last time refreshed to ~new time
		lastRefresh = glfwGetTime() * 1000.0;
	}

	timeDifference = (currentTime - lastTimeDifference);
	lastTimeDifference = currentTime;
}