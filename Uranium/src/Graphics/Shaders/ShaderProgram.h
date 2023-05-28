#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace Uranium::Scenes::Cameras {
	class Camera;
}

namespace Uranium::Graphics::Materials {
	class Material;
}

namespace Uranium::Graphics::Shaders {

	class Shader;

	template<class T> class Uniform;

	/*
	* definition of a shader program
	* as an unsigned int
	*/
	using Program = unsigned int;

	/*
	* Blueprint of a Shader program
	* 
	*/
	class ShaderProgram {
	public:
		/*
		* Custom alias
		*/
		using Camera = Scenes::Cameras::Camera;
		using Material = Materials::Material;

	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		/*
		* initialize the shader program.
		*/
		void init();

		/*
		* Start and stop methods that tells OpenGl
		* when to start using the shaders when rendering
		*/
		void start() const;
		void stop() const;

	public:
		/*
		* getters & setters
		*/

		/*
		* Returns the shader's program ID
		*/
		operator const Program() const;
		
		/*
		* attaches the target shader to 'this' program
		*/
		void attachShader(const std::shared_ptr<Shader>& shader);

		/*
		* load camera settings to shader
		*/
		//void setCamera(const Camera& camera);

		/*
		* load custom material to shader
		*/
		//void setMaterial(const Material& material);

		/*
		*/
		//template<class T> void sendToShader(const Uniform<T>& uniform);

	private:
		/*
		* friends with other classes
		*/
		friend Shader;

	private:
		/*
		* private methods
		*/

		/*
		* This queries the uniform locations
		* that exist inside the shader linked to this
		* shader program
		*/
		void queryUniformLocations();

		/*
		* This links the shaders with the program
		*/
		void link() const;

		/*
		* This validates the shader before using the
		* program. This method has to be called once
		* before starting the shader program
		*/
		void validate() const;

	private:
		/*
		* private members
		*/
		mutable Program program;

		std::vector<std::shared_ptr<Shader>> shaders;
		std::unordered_map<std::string, unsigned int> uniformNames;
	};
}