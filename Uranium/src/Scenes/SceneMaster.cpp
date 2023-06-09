#include <GLFW/glfw3.h>

#include "Core/Application/UraniumApi.h"

#include "Scene.h"
#include "SceneMaster.h"

using namespace Uranium::Scenes;

SceneMaster::SceneMaster(const std::shared_ptr<Window>& window) :
	window(window),
	frameCount(0),
	updateCount(0),
	lastFrame(0),
	lastUpdate(0),
	renderTimer(0),
	updateTimer(0)
{

}

SceneMaster::~SceneMaster() {
	
}

const std::shared_ptr<Scene>& SceneMaster::getCurrentScene() {
	return currentScene;
}

void SceneMaster::setCurrentScene(std::shared_ptr<Scene> scene) {
	this->currentScene = scene;
}

void SceneMaster::renderOutTime() {
	// perform render logic instantly
	currentScene->render();
	// increase udpate count
	frameCount++;
	// display framerate
	if (glfwGetTime() * 1000.0 > lastFrame + 1000.0) {
		print_status("FPS: " << frameCount);
		frameCount = 0;
		// set last time refreshed to ~new time
		lastFrame = glfwGetTime() * 1000.0;
	}
}

void SceneMaster::renderInTime() {
	// calculate elapse time
	double currentFrame = glfwGetTime();
	double elapsedTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// update render timer
	renderTimer += elapsedTime;

	// check if it's time to render
	if (renderTimer >= currentScene->getFrameTime()) {
		// perform rendering logic in time
		currentScene->render();
		// reset rendering timer
		renderTimer = 0.0;
		// increase frame count
		++frameCount;
		// display framerate
		if (frameCount == currentScene->getTargetFramerate()) {
			print_status("FPS : " << frameCount);
			frameCount = 0;
		}
	}
}

void SceneMaster::render() {

	// if no scene is linked, 
	// skip any process
	if (currentScene == nullptr)
		return;
	
	// check if the target framerate
	// must be done instantly
	if (currentScene->getTargetFramerate() == 0) {
		renderOutTime();
	}
	else {
		renderInTime();
	}
}

void SceneMaster::handleSceneLoading() {

	// check if it needs to change to next scene
	if (currentScene->nextScene != nullptr) {
		// copy next scene ref
		std::shared_ptr<Scene> next = currentScene->nextScene;
		// reset the pointer from current
		// of next
		currentScene->nextScene = nullptr;
		// unload the scene content
		currentScene->unload();
		// update flag
		currentScene->is_loaded = false;

		// change scene
		currentScene = next;
	}

	// check if it needs to load the scene
	if (!currentScene->is_loaded) {
		// load new current scene
		currentScene->load();
		// update flag
		currentScene->is_loaded = true;
	}
}

void SceneMaster::updateInTime() {
	// calculate elapse time
	double currentUpdate = glfwGetTime();
	double elapsedTime = currentUpdate - lastUpdate;
	lastUpdate = currentUpdate;

	// update udpate timer
	updateTimer += elapsedTime;

	// check if it's time to update
	if (updateTimer >= currentScene->getUpdateTime()) {

		// perform update logic in time
		currentScene->update();

		// reset udpate timer
		updateTimer = 0.0;

		// increase udpate count
		++updateCount;

		// display updates
		if (updateCount == currentScene->getTargetUpdates()) {
			print_status("UPS : " << updateCount);
			updateCount = 0;
		}
	}
}

void SceneMaster::updateOutTime() {
	// perform update logic instantly
	currentScene->update();

	// increase udpate count
	updateCount++;

	// display updates
	if (glfwGetTime() * 1000.0 > lastUpdate + 1000.0) {
		print_status("UPS: " << updateCount);
		updateCount = 0;
		// set last time refreshed to ~new time
		lastUpdate = glfwGetTime() * 1000.0;
	}
}

void SceneMaster::update() {

	// if no scene is linked, 
	// skip any process
	if (currentScene == nullptr)
		return;

	// handle scene loading
	// when changing is requested
	handleSceneLoading();

	// check if the target updates
	// must be done instantly
	if (currentScene->getTargetUpdates() == 0) {
		updateOutTime();
	}
	else {
		updateInTime();
	}
}

void SceneMaster::unloadCurrentScene() {
	// unlink from any posible next scene
	currentScene->nextScene = nullptr;
	// unload the scene content
	currentScene->unload();
	// update flag
	currentScene->is_loaded = false;
}
