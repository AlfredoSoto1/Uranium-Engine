#include "LayerQueue.h"
#include "Layer.h"

namespace Uranium::Layers {

	LayerQueue::LayerQueue() noexcept :
		layerArrayQueue()
	{

	}

	LayerQueue::~LayerQueue() {
		this->clear();
	}

	LayerQueue::LayerRef LayerQueue::pop() {
		// Move the reference out
		LayerRef ref = std::move(layerArrayQueue.back());
		// Delete the last null reference
		layerArrayQueue.pop_back();

		return ref;
	}

	std::optional<LayerQueue::LayerRef> LayerQueue::last() const {
		return {};
	}

	std::optional<LayerQueue::LayerRef> LayerQueue::front() const {
		return {};
	}

	void LayerQueue::add(LayerRef layer) {
		layerArrayQueue.push_back(std::move(layer));
	}

	void LayerQueue::clear() {
		layerArrayQueue.clear();
	}

	void LayerQueue::onEvent(Event& event) {

	}

	void LayerQueue::onRender() {

	}

	void LayerQueue::onUpdate() {

	}
}