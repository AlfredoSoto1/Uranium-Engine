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

		/*
		* Returns the target updates/frames
		* provided in the setters
		*/
		unsigned int getTargetTicks() const;
		unsigned int getTargetFramerate() const;

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
		* This gets called every frame in the render thread
		* always running in a secured GL-Context
		*/
		virtual void render() = 0;

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

		/*
		* Sets the prefered target ticks/frames
		* to be achieved when rendering/updating the scene
		*/
		void setTargetTicks(unsigned int targetTicks);
		void setTargetFramerate(unsigned int targetFramerate);

		/*
		* Allows the framerate/tick to be measured
		*/
		void allowTickMeasure(bool allow);
		void allowFramerateMeasure(bool allow);

	private:
		bool measureTickrate;
		bool measureFramerate;

		unsigned int targetTicks;
		unsigned int targetFrames;
		
		std::shared_ptr<Scene> nextScene;
	};
}