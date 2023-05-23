#pragma once

#include "DataStructures/Containers/Container.h"

namespace Uranium::DataStructures::Lists {

	template<class Element> class List : public Containers::Container<Element> {
	public:

		/**
		 * Adds a copy of the element to the end of the List
		 * @param obj - The element to add to the List
		 */
		virtual void add(const Element& obj) = 0;

		/**
		 * Adds a copy of the element to the position given by index.
		 * @param index - position we want to add the element to.
		 * @param obj - the element we wish to add
		 * @throws an exception if the index is not valid
		 */
		virtual void add(unsigned int index, const Element& obj) = 0;

		/**
		 * Returns the value at the given position
		 * @param index - position of the value we want
		 * @throws an exception if the index is not valid
		 * @return (Element) value at position index
		 */
		virtual Element& get(unsigned int index) = 0;

		/**
		 * Replaces the value at the position given by index.
		 * @param index - position we want to replace
		 * @param obj - the new value we want to place
		 * @throws an exception if the index is not valid
		 * @return (Element) before replacing with new element
		 */
		virtual Element set(int index, const Element& obj) = 0;

		/**
		 * Removes the element at position index
		 * @param index - The position of the element we want to remove
		 * @return (boolean) Always true since the position has to be valied (exist) to be removed.
		 * @throws an exception if the index is not valid
		 */
		virtual void removeIndex(unsigned int index) = 0;

		/**
		 * Removes the first instance of the element obj.
		 * @param obj - the value we want to remove
		 * @return (boolean) Whether the element was successfully found and removed. True if removed, false otherwise.
		 */
		virtual bool remove(const Element& obj) = 0;

		/**
		 * Removes every instance of element obj.
		 * @param obj - the value we want to remove
		 * @return (unsigned int) number of entries that were removed.
		 */
		virtual unsigned int removeAll(const Element& obj) = 0;

		/*
		* Returns a boolean (true) - if element is found inside
		* the container, (false) - otherwise
		*/
		virtual bool contains(const Element& obj) = 0;

		/**
		 * Returns the position where an instance of obj first appears.
		 * @param obj - obj we want to search for
		 * @return (unsigned int) position where obj first appears in the List
		 */
		virtual unsigned int firstIndex(const Element& obj) = 0;

		/**
		 * Returns the position where an instance of obj last appears.
		 * @param obj - obj we want to search for
		 * @return (unsigned int) position where obj last appears in the List
		 */
		virtual unsigned int lastIndex(const Element& obj) = 0;

		/**
		 * Returns the first element in the List
		 * @return (Element) First element in the List
		 */
		virtual Element& first() = 0;
		/**
		 * Returns the last element in the List.
		 * @return (Element) last element in the List
		 */
		virtual Element& last() = 0;

	};
}