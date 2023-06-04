#include <GLFW/glfw3.h>

#include <stdexcept>

#include "Scene.h"
#include "Graphics/Renderer/SceneRenderer.h"

using namespace Uranium::Scenes;
using namespace Uranium::Graphics::Renderer;

Scene::Scene() :
	nextScene(nullptr),
	sceneName("Default"),
	targetUpdates(Scene::DEFAULT_60),
	targetFrames(Scene::DEFAULT_60),
	is_paused(false),
	is_loaded(false)
{
	renderer = new SceneRenderer();
}

Scene::~Scene() {
	// remove all linked scenes
	// from this one
	linkedScenes.clear();

	delete renderer;
}

bool Scene::isPaused() const {
	return is_paused;
}

bool Scene::isLoaded() const {
	return is_loaded;
}

std::string Scene::getName() const {
	return sceneName;
}

SceneRenderer& Scene::getRenderer() const {
	return *renderer;
}

const std::vector<std::shared_ptr<Scene>>& Scene::getLinkedScenes() const {
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

unsigned int Scene::getTargetUpdates() const {
	return targetUpdates;
}
unsigned int Scene::getTargetFramerate() const {
	return targetFrames;
}

double Scene::getFrameTime() const {
	return 1.0 / targetFrames;
}

double Scene::getUpdateTime() const {
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
