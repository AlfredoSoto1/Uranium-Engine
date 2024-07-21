#pragma once

#include "Window.h"

namespace Uranium::Platform::Display {

	class OpenGLWindow final : public Window {
	public:
		explicit OpenGLWindow() noexcept;
		
		~OpenGLWindow();

	public:
		/*
		* Set custom modes
		*/
		void setVisible(bool visible) override;
		void setResizable(bool resizable) override;
		void setDecorated(bool decorated) override;
		void setAlwaysOnTop(bool alwaysOnTop) override;
		
		/*
		* Set custom operations
		*/
		void restore() override;
		void maximize() override;
		void minimize() override;

		void close() override;
		void focus() override;
		void requestAttention() override;

		void center(MonitorRef monitor) override;
		void setFullscreen(MonitorRef monitor) override;

	};
}