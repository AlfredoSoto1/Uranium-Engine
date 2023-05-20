#include <GLFW/glfw3.h>

#include "Scene.h"
#include <stdexcept>

using namespace Uranium::Scenes;

Scene::Scene() :
	nextScene(nullptr),
	sceneName("Default"),
	targetUpdates(Scene::DEFAULT_60),
	targetFrames(Scene::DEFAULT_60),
	is_paused(false),
	is_loaded(false)
{

}

Scene::~Scene() {
	
}

bool Scene::isPaused() {
	return is_paused;
}

bool Scene::isLoaded() {
	return is_loaded;
}

std::string Scene::getName() {
	return sceneName;
}

const std::vector<std::shared_ptr<Scene>>& Scene::getLinkedScenes() {
	return linkedScenes;
}

void Scene::setName(const std::string& name) {
	this->sceneName = name;
}

void Scene::linkScene(const std::shared_ptr<Scene>& scene) {
	if (scene == nullptr)
		throw std::invalid_argument("Scene parameter cannot be null");
	linkedScenes.push_back(scene);
}

void Scene::setTargetUpdate(unsigned int targetUpdate) {
	this->targetUpdates = targetUpdate;
}

void Scene::setTargetFramerate(unsigned int targetFramerate) {
	this->targetFrames = targetFramerate;
}

unsigned int Scene::getTargetUpdates() {
	return targetUpdates;
}
unsigned int Scene::getTargetFramerate() {
	return targetFrames;
}

double Scene::getFrameTime() {
	return 1.0 / targetFrames;
}

double Scene::getUpdateTime() {
	return 1.0 / targetUpdates;
}

void Scene::pause() {
	is_paused = true;
}

void Scene::resume() {
	is_paused = false;
}

void Scene::changeScene(const std::shared_ptr<Scene>& scene) {
	// change to next
	nextScene = scene; 
}
