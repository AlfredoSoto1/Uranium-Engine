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
	
}

bool Scene::isPaused() {
	return is_paused;
}

std::string Scene::getName() {
	return sceneName;
}

std::shared_ptr<Scene> Scene::getNext() {
	return nextScene;
}

void Scene::setName(const std::string& name) {
	this->sceneName = name;
}

void Scene::setNext(std::shared_ptr<Scene> scene) {
	nextScene = scene;
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
