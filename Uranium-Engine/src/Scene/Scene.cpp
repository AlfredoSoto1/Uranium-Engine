#include <GL/glfw3.h>
#include <stdexcept>

#include "Scene.h"

namespace Uranium::Scene {

	Scene::Scene() noexcept :
		targetUpdates(Scene::DEFAULT_60),
		targetFrames(Scene::DEFAULT_60)
	{

	}

	Scene::~Scene() {
		nextScene = nullptr;
	}

	std::shared_ptr<Scene> Scene::getNextScene() const {
		return nextScene;
	}

	void Scene::setNextScene(std::shared_ptr<Scene> next) {
		nextScene = next;
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
}
