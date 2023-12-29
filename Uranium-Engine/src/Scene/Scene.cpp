#include <GL/glfw3.h>

#include "Scene.h"

namespace Uranium::Scene {

	Scene::Scene() noexcept :
		nextScene(nullptr),
		targetTicks(60) // 60 default
	{

	}

	Scene::~Scene() {
		
	}

	unsigned int Scene::getTargetTicks() const {
		return targetTicks;
	}

	void Scene::setTargetTicks(unsigned int targetTicks) {
		this->targetTicks = targetTicks;
	}

	std::shared_ptr<Scene> Scene::getNextScene() const {
		return nextScene;
	}

	void Scene::setNextScene(std::shared_ptr<Scene> next) {
		nextScene = next;
	}
}
