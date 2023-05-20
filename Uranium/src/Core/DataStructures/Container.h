#pragma once

namespace Uranium::Core::DataStructures {

	class Container {
	public:
		/*
		* Returns the size of the Container.
		* @return (unsgined int) size of the Container
		*/
		virtual inline unsigned int size() = 0;

		/*
		 * Returns whether the Container is empty of not.
		 * True if empty, false otherwise.
		 * @return (boolean) whether the Container is empty
		 */
		virtual inline bool isEmpty() = 0;

		/**
		 * Empties the container.
		 */
		virtual void clear() = 0;
	};
}