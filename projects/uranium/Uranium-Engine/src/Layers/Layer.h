#pragma once

namespace Uranium::Input::Events {
	class Event;
}

namespace Uranium::Layers {

	namespace States {
		class State;
	}

	namespace Scenes {
		class Scene;
	}

	class Layer {
	public:
		explicit Layer() noexcept;
		
		virtual ~Layer();

	public:
		using Event = Input::Events::Event;

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onRender() = 0;
		virtual void onUpdate() = 0;
		virtual void onEvent(Event& event) = 0;

	public:
		bool isEnabled() const;
		void setEnabled(bool enable);

	protected:
		using StateRef = std::unique_ptr<States::State>;
		using SceneRef = std::unique_ptr<Scenes::Scene>;

	private:
		bool enabled;
		bool respondsToEvents;
		unsigned int layerNumber;

		std::vector<StateRef> states;
		std::vector<SceneRef> scenes;
	};
}