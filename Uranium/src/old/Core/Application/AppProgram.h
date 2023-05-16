#pragma once

#include <vector>

namespace Uranium::Core::Application {

	namespace UApp   = Uranium::Core::Application;
	namespace USenes = Uranium::Scenes;

	class UApp::Application;
	class USenes::Scene;

	class AppProgram {
	private:
		friend USenes::Scene;
		friend UApp::Application;

		bool hasChangedScene;

		std::vector<USenes::Scene*> activeScenes;

		USenes::Scene* currentScene;

		void draw();
		void afterDraw();
		void update();

	public:
		virtual void init() = 0;
		virtual void dispose() = 0;
		
		AppProgram();
		virtual ~AppProgram();

		void push_firstNewScene(USenes::Scene* _scenePtr);
	};
}