#pragma once

#include <vector>
#include <memory>
#include <optional>

namespace Uranium::Input::Events {
	class Event;
}

namespace Uranium::Layers {

	class Layer;

	class LayerQueue final {
	public:
		explicit LayerQueue() noexcept;

		~LayerQueue();

	public:
		using Event = Input::Events::Event;
		using LayerRef = std::unique_ptr<Layer>;

		/*
		* Removes the last layer entered to the queue
		*/
		LayerRef pop();

		/*
		* Returns an optional containing the abstract layer instance:
		* Last  -> returns the last layer of the queue
		* First -> returns the first layer of the queue
		*/
		std::optional<LayerRef> last() const;
		std::optional<LayerRef> front() const;
		
		/*
		* Adds a unique layer to the queue
		*/
		void add(LayerRef layer);

		/*
		* Clears the queue
		*/
		void clear();
		
		/*
		* Updates the events from back to front of the queue
		*/
		void onEvent(Event& event);

		/*
		* Renders the layers from front to back
		*/
		void onRender();
		
		/*
		* Updates the layers from front to back
		*/
		void onUpdate();

	private:
		std::vector<LayerRef> layerArrayQueue;
	};
}