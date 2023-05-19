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
		volatile double getTimeInstance();
		
		std::shared_ptr<Scene> getCurrentScene();

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
		void postUpdate();

		void sleepScene(const unsigned int targetTick, const unsigned int triggerTarget, volatile double* lastTick);

	private:
		/*
		* private members
		*/
		volatile unsigned int frameCount;

		volatile double lastFrame;

		volatile double lastRefresh;
		volatile double timeDifference;
		volatile double lastTimeDifference;

		std::shared_ptr<Scene> currentScene;

	};
}