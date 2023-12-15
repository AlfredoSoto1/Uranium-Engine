#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Uranium::Graphics::Renderer {
	class SceneRenderer;
}

namespace Uranium::Scenes {

	class SceneManager;

	class Scene {
	public:
		/*
		* custom alias
		*/
		using SceneRenderer = Graphics::Renderer::SceneRenderer;

	public:
		/*
		* Public static declarations
		*/
		static constexpr unsigned int DEFAULT_60 = 60;
		static constexpr unsigned int UNLIMITED_FPS = 0;
		static constexpr unsigned int UNLIMITED_UPS = 0;

	public:
		/*
		* Default constructor
		*/
		Scene();

		/*
		* default destructor
		*/
		virtual ~Scene();

	public:
		/*
		* getters
		*/
		/*
		* Returns the name of the scene
		*/
		std::string getName() const;

		/*
		* Returns the renderer asociated
		* with 'this' scene
		*/
		SceneRenderer& getRenderer() const;

		/*
		* Returns a list containing a reference
		* to the scenes that 'this' scene instance
		* is awear of and its capable of switching to
		*/
		const std::vector<std::shared_ptr<Scene>>& getLinkedScenes() const;

		/*
		* Returns a boolean returning true
		* if 'this' scene is either paused or loaded.
		* False will be returned otherwise
		*/
		bool isPaused() const;
		bool isLoaded() const;

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
		* setters
		*/

		/*
		* Sets the name of 'this' scene instance
		*/
		void setName(const std::string& name);

		/*
		* Links the scene to another
		*/
		void linkScene(const std::shared_ptr<Scene>& scene);

		/*
		* Sets the prefered target update/frames
		* to be achieved when rendering/updating the scene
		*/
		void setTargetUpdate(unsigned int targetUpdate);
		void setTargetFramerate(unsigned int targetFramerate);

	protected:
		/*
		* abstract methods
		*/
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

	protected:
		/*
		* protected methods
		*/

		/*
		* Pauses/resumes 'this' scene instance
		*/
		void pause();
		void resume();

		/*
		* Tells the SceneManager to which scene change to
		*/
		void changeScene(const std::shared_ptr<Scene>& scene);
	
	private:
		/*
		* Friends with other classes
		*/
		friend SceneManager;

	private:
		/*
		* Private members
		*/
		unsigned int targetFrames;
		unsigned int targetUpdates;

		bool is_paused;
		bool is_loaded;

		SceneRenderer* renderer;

		std::string sceneName;

		std::shared_ptr<Scene> nextScene;

		std::vector<std::shared_ptr<Scene>> linkedScenes;

	};
}