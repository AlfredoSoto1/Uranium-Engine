#pragma once

#include "Graph.h"
#include <unordered_map>

namespace Uranium::Core::DataStructures {

	template<class Element> class SparseGraph : public Graph<Element> {
	public:
		explicit SparseGraph();
		~SparseGraph();

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

	private:
		/*
		* private members
		*/
		std::unordered_map<Element, Element> adjList;

	};
}