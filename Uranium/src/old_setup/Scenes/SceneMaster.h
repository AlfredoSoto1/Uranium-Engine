#pragma once

#include <memory>

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Core::Application {
	class ApplicationProgram;
}

namespace Uranium::Scenes {

	class Scene;

	class SceneMaster {
	public:
		/*
		* custom alias
		*/
		using Window = Graphics::Display::Window;
		using ApplicationProgram = Core::Application::ApplicationProgram;

	public:
		virtual ~SceneMaster();

	public:
		/*
		* public methods
		*/
		const std::shared_ptr<Scene>& getCurrentScene();

		void setCurrentScene(std::shared_ptr<Scene> scene);

	private:
		/*
		* Friends with other classes
		*/
		friend ApplicationProgram;

	private:
		/*
		* private methods
		*/
		/*
		* copy and move constructors are 
		* deleted because we don't need them
		*/
		SceneMaster(const SceneMaster&) = delete;
		SceneMaster(const SceneMaster&&) = delete;

		/*
		* Creates center crontrol that manages
		* all scenes in our Application program
		*/
		SceneMaster(const std::shared_ptr<Window>& window);
		
		/*
		* handles render and update of
		* current scene
		*/
		void render();
		void update();

		/*
		* This gets in charge of loading and
		* unloading a scene in memory
		*/
		void handleSceneLoading();

		/*
		* This method gets called when program 
		* has ended. The reason is to free resources
		* from last scene before closing program
		*/
		void unloadCurrentScene();

		/*
		* These manages the rendering of
		* the current scene synchronized
		*/
		void renderInTime();
		void renderOutTime();

		void updateInTime();
		void updateOutTime();

	private:
		/*
		* private members
		*/
		volatile unsigned int frameCount;
		volatile unsigned int updateCount;

		volatile double lastFrame;
		volatile double lastUpdate;

		volatile double renderTimer;
		volatile double updateTimer;

		std::shared_ptr<Window> window;
		std::shared_ptr<Scene> currentScene;

	};
}