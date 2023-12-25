#include <GL/glfw3.h>

#include "Scene.h"

namespace Uranium::Scene {

	Scene::Scene() noexcept :
		nextScene(nullptr)
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
}
