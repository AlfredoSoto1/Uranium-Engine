#include <GL/glfw3.h>

#include "Scene.h"

namespace Uranium::Scene {

	Scene::Scene() noexcept :
		nextScene(nullptr),
		targetTicks(60u),
		targetFrames(60u),
		measureTickrate(false),
		measureFramerate(false)
	{

	}

	Scene::~Scene() {
		
	}

	std::shared_ptr<Scene> Scene::getNextScene() const {
		return nextScene;
	}

	void Scene::setNextScene(std::shared_ptr<Scene> next) {
		nextScene = next;
	}

	void Scene::setTargetTicks(unsigned int targetTicks) {
		this->targetTicks = targetTicks;
	}

	void Scene::setTargetFramerate(unsigned int targetFramerate) {
		this->targetFrames = targetFramerate;
	}

	void Scene::allowTickMeasure(bool allow) {
		measureTickrate = allow;
	}

	void Scene::allowFramerateMeasure(bool allow) {
		measureFramerate = allow;
	}

	unsigned int Scene::getTargetTicks() const {
		return targetTicks;
	}

	unsigned int Scene::getTargetFramerate() const {
		return targetFrames;
	}
}
