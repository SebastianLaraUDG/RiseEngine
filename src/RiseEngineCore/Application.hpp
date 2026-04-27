#pragma once
#include <memory>

#include <RiseEngineCore/Core/CoreCommon.hpp>
#pragma warning(disable : 4251) // Remove warning C4251: class 'std::unique_ptr<...>' needs to have dll-interface to be used by clients of class '...'. This is because the unique_ptr is not exported from the DLL, but it is used in the public interface of the Application class. To fix this, we can either export the unique_ptr or we can use a raw pointer instead.
#include <RiseEngineCore/Window.hpp>
#include <Rendering/include/Renderer.hpp>
#include <Rendering/include/VAO.hpp>
#include <Rendering/include/VBO.hpp>
#include <chrono>

#include "RiseEngine.hpp"

/* Camera class, initial abstraction.
class Camera
{
public:
	Camera(Vector3f location)
	{
		transform.location = location;
		transform.rotation = Vector3f(0.f, 0.f, 0.f);

		target = Vector3f(0.f, 0.f, 0.f);
		CalculateCameraUp();
		viewAlpha = 45.f;
		near = 0.1f;
		far = 100.f;
	}
	struct Transform
	{
		Vector3f location;
		Vector3f rotation; // Should be a quaternion but TODO.
	};

	Transform transform;
	Vector3f target;
	Vector3f direction; // From the camera to the target. NOTE: it is actually pointing in the reverse direction of what it is targeting.
	Vector3f up; // Camera local up vector.
	inline static const Vector3f worldUp = Vector3f::UpVector();
	f32 viewAlpha; // Pyramid aperture.
	f32 near;
	f32 far;

	void updateCameraDirection()
	{
		direction = (transform.location - target).GetNormal();
	}

	void CalculateCameraUp()
	{
		updateCameraDirection();
		auto cameraRight = Vector3f::CrossProduct(direction, worldUp);
		up = Vector3f::CrossProduct(cameraRight, target);
	}
};
*/

namespace RiseEngine
{

	class RISE_API Application
	{
	public:
		Application();
		explicit Application(int32 windowWidth, int32 windowHeight, const char* title);
		virtual ~Application();

		void Run();
	protected:
		void Update();
		void Render() const;
		void ProcessInput();

	protected:
		void Init(int32 width, int32 height, const char* title);
		void InitFileSystem();

	private:

		std::unique_ptr<Window> window_;
		std::unique_ptr<Renderer> renderer_;

		std::unique_ptr<Shader> shader_; // The unique global shader of the program.

		/* Temporal, remove. */
		std::unique_ptr<VAO> vao;
		std::unique_ptr<VBO> vbo;

		// Time management.
		std::chrono::steady_clock::time_point lastFrame;
		double deltaTime_; // Time between current frame and last frame.
	};

}