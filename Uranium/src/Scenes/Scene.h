#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Uranium::Scenes {

	class SceneMaster;

	class Scene {
	public:
		/*
		* Public static declarations
		*/
		static constexpr unsigned int UNLIMITED_FPS = 0;

	public:
		Scene();
		virtual ~Scene();

	public:
		/*
		* Public methods
		*/
		bool isPaused();

		std::string getName();

		void setName(const std::string& name);
		void linkScene(std::shared_ptr<Scene> scene);

		void setGameTick(unsigned int gameTick);
		void setTargetFramerate(unsigned int targetFramerate);

		unsigned int getGameTick();
		unsigned int getTargetFramerate();

	protected:
		/*
		* Protected methods
		*/
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void dispose() = 0;

		virtual void reset();

		void pause();
		void resume();
	
	private:
		/*
		* Friends with other classes
		*/
		friend SceneMaster;

	private:
		/*
		* Private methods
		*/

	private:
		/*
		* Private members
		*/
		unsigned int gameTick;
		unsigned int targetFrames;

		bool is_paused;

		std::string sceneName;

		std::vector<std::shared_ptr<Scene>> scenes;

	};
}