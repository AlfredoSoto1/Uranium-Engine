#pragma once

namespace Uranium::Input::Listeners {

	class WindowListener {
	public:
		/*
		* Public abstract listeners
		*/
		virtual void onClose() = 0;

		virtual void onMoved(int xpos, int ypos) = 0;
		virtual void onResize(unsigned int width, unsigned int height) = 0;

		virtual void onFocus() = 0;
		virtual void offFocus() = 0;

		virtual void onRestored() = 0;
		virtual void onMaximized() = 0;
		virtual void onMinimized() = 0;

		virtual void onCanvasRefresh() = 0;
		virtual void onFramebufferResize(unsigned int width, unsigned int height) = 0;
	};
}