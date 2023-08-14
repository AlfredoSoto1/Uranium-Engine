#include <iostream>
#include <string>

#include "AppProgram.h"
#include "Scenes/Scene.h"

using namespace Uranium::Scenes;
using namespace Uranium::Core::Application;

AppProgram::AppProgram()
{
	hasChangedScene = false;
	currentScene = nullptr;
}

AppProgram::~AppProgram() {
	activeScenes.clear();
}

void AppProgram::push_firstNewScene(Scene* _scenePtr) {
	activeScenes.push_back(_scenePtr);
	currentScene = _scenePtr;
	hasChangedScene = true;
}

void AppProgram::update() {
	if (activeScenes.empty()) {
		std::cerr << "No scenes available" << std::endl;
		return;
	}

	// load scene once after scene has changed
	if (hasChangedScene) {
		currentScene->load();
		hasChangedScene = false;
	}

	// update scene content
	currentScene->update();

	// change scene to next
	if (!currentScene->hasToChangeScene())
		return;

	// unload scene content
	currentScene->unload();

	// linear search for the next scene
	bool foundScene_toChange = false;
	for (Scene* scene : activeScenes) {
		if (currentScene->getNextScene().compare(scene->getName()) != 0)
			continue;
		currentScene = scene;
		foundScene_toChange = true;
		break;
	}

	// if no next scene is found, current scene will be set to the first scene
	if (!foundScene_toChange) {
		currentScene = activeScenes[0];
	}

	// reset scene
	currentScene->reset();

	hasChangedScene = true;
}

void AppProgram::draw() {
	currentScene->draw();
}

void AppProgram::afterDraw() {
	currentScene->postDraw();
}
