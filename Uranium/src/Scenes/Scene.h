#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Uranium::Scenes {

	class SceneMaster;

	class Scene {
	public:
		/*
		* Public static declarations
		*/
		static constexpr unsigned int DEFAULT_60 = 60;
		static constexpr unsigned int UNLIMITED_FPS = 0;
		static constexpr unsigned int UNLIMITED_UPS = 0;

	public:
		Scene();
		virtual ~Scene();

	public:
		/*
		* getters and setters
		*/
		std::string getName();

		const std::vector<std::shared_ptr<Scene>>& getLinkedScenes();

		bool isPaused();
		bool isLoaded();

		double getFrameTime();
		double getUpdateTime();

		unsigned int getTargetUpdates();
		unsigned int getTargetFramerate();

	public:
		/*
		* setters
		*/
		void setName(const std::string& name);
		void linkScene(const std::shared_ptr<Scene>& scene);

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
		void pause();
		void resume();

		void changeScene(const std::shared_ptr<Scene>& scene);
	
	private:
		/*
		* Friends with other classes
		*/
		friend SceneMaster;

	private:
		/*
		* Private members
		*/
		unsigned int targetFrames;
		unsigned int targetUpdates;

		bool is_paused;
		bool is_loaded;

		std::string sceneName;

		std::shared_ptr<Scene> nextScene;

		std::vector<std::shared_ptr<Scene>> linkedScenes;

	};
}