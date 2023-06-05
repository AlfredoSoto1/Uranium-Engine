#pragma once

#include <vector>
#include <unordered_map>

namespace Uranium::Graphics::Materials {
	class Assets;
	class Material;
}

namespace Uranium::Graphics::Shaders {
	class ShaderProgram;
	class ShaderMaterial;
}

namespace Uranium::Scenes::Objects {

	class Entity;

	/*
	* Entity Collection
	*
	*/
	class EntityCollection {
	public:
		/*
		* Custom alias
		*/
		template<class Key, class Value> using HashMap = std::unordered_map<Key, Value>;

	public:
		/*
		*/

		void insert();
		
	private:
		/*
		* Private methods
		*/

	private:
		/*
		* Private members
		*/
		HashMap<int, int> collection;
	};
}