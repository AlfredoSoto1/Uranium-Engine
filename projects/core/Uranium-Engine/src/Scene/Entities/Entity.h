#pragma once

#include <string>
#include <memory>

namespace Uranium::Scene::Entities {

	class Entity {
	public:
		/*
		*/
		Entity() noexcept;
		
		virtual ~Entity();
		
	public:
		/*
		*/
		virtual unsigned int getId() const = 0;
		
		/*
		*/
		virtual std::string getName() const = 0;

	public:
	};
}