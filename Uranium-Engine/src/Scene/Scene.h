#pragma once

#include <memory>

namespace Uranium::Engine {
	class SceneManager;
}

namespace Uranium::Scene {

	class Scene {
	public:
		friend Engine::SceneManager;

	public:
		/*
		* Returns a reference of the next scene to be changed
		*/
		std::shared_ptr<Scene> getNextScene() const;

	public:
		/*
		* Sets the next scene to be changed after event
		*/
		void setNextScene(std::shared_ptr<Scene> next);

	protected:
		/*
		* Construct an abstract Scene
		*/
		explicit Scene() noexcept;

		virtual ~Scene();

	protected:
		/*
		* These methods get called in context when
		* it needs to load / unload the scene
		*/
		virtual void load() = 0;
		virtual void unload() = 0;

		/*
		* Resets the scene content
		*/
		virtual void reset() = 0;

	private:
		std::shared_ptr<Scene> nextScene;
	};
}