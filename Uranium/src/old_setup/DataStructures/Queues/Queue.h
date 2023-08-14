#pragma once

#include "DataStructures/Containers/Container.h"

namespace Uranium::DataStructures::Queues {

	template<class Element> class Queue : public Containers::Container<Element> {
	public:

		/*
		*/
		virtual Element* front() = 0;

		/*
		*/
		virtual void enqueue(const Element& obj) = 0;
		
		/*
		*/
		virtual void dequeue(const Element& obj) = 0;
	};
}