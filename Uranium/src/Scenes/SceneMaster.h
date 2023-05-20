#pragma once

#include <memory>

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
		using ApplicationProgram = Uranium::Core::Application::ApplicationProgram;

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
		SceneMaster();
		SceneMaster(const SceneMaster&) = delete;
		SceneMaster(const SceneMaster&&) = delete;
		
		void render();
		void update();

		void handleSceneLoading();

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

		std::shared_ptr<Scene> currentScene;

	};
}