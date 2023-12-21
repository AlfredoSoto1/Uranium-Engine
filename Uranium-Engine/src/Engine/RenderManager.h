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
		// TODO temp method
		void render();

	private:

	};
}