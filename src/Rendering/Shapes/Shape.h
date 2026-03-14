#pragma once
#include <Runtime/MainFramework/Public/Entity.h>
#include <Rendering/include/VAO.h>
#include <Rendering/include/VBO.h>
class Shader;

/*
TODO: for simplicity this Shape class will be a cube until 3D rendering is tested, then
implement rendering login in the approppriate component class.
*/
class Shape : public Entity
{
public:
	Shape();
	~Shape(){}

	static std::vector<float> VERTICES_DATA;

	void render() const; // TODO: the objects should not be rendered here, the responsible for rendering
	// should be a specific (rendering component), but for now I will render here for testing purposes.
protected:
	VAO vao_;
	VBO vbo_;
	std::unique_ptr<Shader> shader_;
};

