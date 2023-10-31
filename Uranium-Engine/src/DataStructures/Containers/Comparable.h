#pragma once

namespace Uranium::DataStructures::Containers {

	template<class Element> class Comparable {
	public:
		/*
		* returns an integer to indicate the
		* comparison as (are equal == 0), (not equal != 0)
		*/
		virtual int compareTo(const Element& obj) = 0;
	};
}