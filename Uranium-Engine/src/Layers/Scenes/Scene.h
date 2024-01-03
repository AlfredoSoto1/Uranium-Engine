#pragma once

#include <memory>

namespace Uranium::Engine {
	class SceneManager;
}

namespace Uranium::Layers::Scenes {

	class Scene {
	public:
		friend Engine::SceneManager;

	public:
		/*
		* Returns a reference of the next scene to be changed
		*/
		std::shared_ptr<Scene> getNextScene() const;

		/*
		* Returns the target ticks
		*/
		unsigned int getTargetTicks() const;

	public:
		/*
		* Sets the next scene to be changed after event
		*/
		void setNextScene(std::shared_ptr<Scene> next);

		/*
		* Sets the target ticks
		*/
		void setTargetTicks(unsigned int tagetTicks);

	protected:
		/*
		* Construct an abstract Scene
		*/
		explicit Scene() noexcept;

		virtual ~Scene();

	protected:
		/*
		* Updates the scene
		*/
		virtual void update() = 0;

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
		unsigned int targetTicks;

		std::shared_ptr<Scene> nextScene;
	};
}