//#pragma once
//
//#include <vector>
//#include <unordered_map>
//
//namespace Uranium::Scenes::Cameras {
//	class Camera;
//}
//
//namespace Uranium::Scenes::Objects {
//	class Entity;
//}
//
//namespace Uranium::Graphics::Meshes {
//	class Model;
//}
//
//namespace Uranium::Graphics::Shaders {
//	class ShaderMaterial;
//	class ShaderProgram;
//}
//
//namespace Uranium::Graphics::Renderer {
//
//	class Renderable;
//
//	/*
//	* Blueprint of GroupRenderer class
//	*/
//	class GroupRenderer {
//	public:
//		/*
//		* custom alias
//		*/
//		using Model = Meshes::Model;
//		using Camera = Scenes::Cameras::Camera;
//		using Entity = Scenes::Objects::Entity;
//		using ShaderProgram = Shaders::ShaderProgram;
//		using ShaderMaterial = Shaders::ShaderMaterial;
//
//		using ShadedModel = std::pair<std::shared_ptr<Model>&, std::shared_ptr<ShaderMaterial>&>;
//	
//	public:
//		GroupRenderer();
//		virtual ~GroupRenderer();
//
//		void draw();
//		void prepareRenderStates();
//		void cleanUpRenderStates();
//
//	public:
//		/*
//		* getters and setters
//		*/
//
//	private:
//		/*
//		* private methods
//		*/
//
//	private:
//		/*
//		* private members
//		*/
//		std::shared_ptr<ShaderProgram> shaderProgram;
//		std::unordered_map<ShadedModel, std::vector<std::shared_ptr<Renderable>>> renderingGroup;
//
//	};
//}