#pragma once

namespace Uranium::Engine {

	class RenderManager final {
	public:
		friend class BaseEngine;

	public:
		~RenderManager();

		/*
		* Delete the copy/move constructors
		* we just need one render manager instance inside the engine
		*/
		RenderManager(RenderManager&) = delete;
		RenderManager(RenderManager&&) = delete;
		RenderManager& operator=(const RenderManager&) = delete;

	private:
		/*
		* 
		*/
		explicit RenderManager() noexcept;

	private:
		/*
		* 
		*/
		void render();

		void linearRender();

	private:
		double lastFrame;
		double lastMeasuredFrame;
		double elapsedRenderTime;

		unsigned int frameCount;
		unsigned int targetFramerate;
	};
}