#pragma once

#include <type_traits>
#include "ShaderTypes.h"

namespace Uranium::Core::Math {
	struct vec2;
	struct vec3;
	struct vec4;
	struct mat2;
	struct mat3;
	struct mat4;
}

namespace Uranium::Graphics::Shaders {

	template<class T> class Uniform {
	public:
		/*
		* Custom Alias
		*/
		using vec2 = Core::Math::vec2;
		using vec3 = Core::Math::vec3;
		using vec4 = Core::Math::vec4;
		
		using mat2 = Core::Math::mat2;
		using mat3 = Core::Math::mat3;
		using mat4 = Core::Math::mat4;

		/*
		* Throw a compile error if the type 
		* doesn't match the established types for
		* 'this' Uniform instance class
		*/
		static_assert(
			std::is_same<T, vec2>::value           || 
			std::is_same<T, vec3>::value           ||
			std::is_same<T, vec4>::value           ||

			std::is_same<T, mat2>::value           ||
			std::is_same<T, mat3>::value           ||
			std::is_same<T, mat4>::value           ||

			std::is_same<T, int>::value            ||
			std::is_same<T, char>::value           ||
			std::is_same<T, float>::value          ||
			std::is_same<T, double>::value         ||
			std::is_same<T, unsigned int>::value   ||
			std::is_same<T, unsigned char>::value,
			
			"Incompatible template argument for Uniform, must be : "
			"vectors, matrices or int, double, float, unsigned int");
	public:

		Uniform() = delete;

		Uniform(const T& data) :
			data(data)
		{
			
		}

		Uniform(T&& data) :
			data(std::move(data))
		{
			
		}

		operator T& () {
			return data;
		}

	private:
		/*
		* private members
		*/
		T data;
	};
}