#include <GLFW/glfw3.h>

#include "Scene.h"

using namespace Uranium::Scenes;

Scene::Scene() :
	sceneName("Default"),
	gameTick(0),
	targetFrames(Scene::UNLIMITED_FPS),
	is_paused(false)
{

}

Scene::~Scene() {
	
	// clear all scene references
	scenes.clear();
}

bool Scene::isPaused() {
	return is_paused;
}

std::string Scene::getName() {
	return sceneName;
}

void Scene::setName(const std::string& name) {
	this->sceneName = name;
}

void Scene::linkScene(std::shared_ptr<Scene> scene) {
	scenes.push_back(scene);
}

void Scene::setGameTick(unsigned int gameTick) {
	this->gameTick = gameTick;
}

void Scene::setTargetFramerate(unsigned int targetFramerate) {
	this->targetFrames = targetFramerate;
}

unsigned int Scene::getGameTick() {
	return gameTick;
}
unsigned int Scene::getTargetFramerate() {
	return targetFrames;
}

void Scene::reset() {

}

void Scene::pause() {
	is_paused = true;
}

void Scene::resume() {
	is_paused = false;
}
