#pragma once

#include <memory>
#include <vector>

namespace Uranium::Engine {
	class SceneManager;
}

namespace Uranium::Scene {

	class Scene {
	private:
		friend Engine::SceneManager;

	public:
		static constexpr unsigned int DEFAULT_60 = 60;
		static constexpr unsigned int UNLIMITED_FPS = 0;
		static constexpr unsigned int UNLIMITED_UPS = 0;
	
	public:
		/*
		* Returns a reference of the next scene to be changed
		*/
		std::shared_ptr<Scene> getNextScene() const;

		/*
		* Returns the time it takes a 
		* single frame/update to execute
		*/
		double getFrameTime() const;
		double getUpdateTime() const;

		/*
		* Returns the target updates/frames
		* provided in the setters
		*/
		unsigned int getTargetUpdates() const;
		unsigned int getTargetFramerate() const;

	public:
		/*
		* Sets the next scene to be changed after event
		*/
		void setNextScene(std::shared_ptr<Scene> next);

		/*
		* Sets the prefered target update/frames
		* to be achieved when rendering/updating the scene
		*/
		void setTargetUpdate(unsigned int targetUpdate);
		void setTargetFramerate(unsigned int targetFramerate);

	protected:
		/*
		* Construct an abstract Scene
		*/
		explicit Scene() noexcept;

		virtual ~Scene();

	protected:
		/*
		* These methods get called in context
		* when updating / rendering the scene
		*/
		virtual void update() = 0;
		virtual void render() = 0;

		/*
		* These methods get called in context when
		* it needs to load / unload the scene
		*/
		virtual void load() = 0;
		virtual void unload() = 0;

	private:
		unsigned int targetFrames;
		unsigned int targetUpdates;
		
		std::shared_ptr<Scene> nextScene;
	};
}