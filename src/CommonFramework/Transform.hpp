#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RiseEngine
{
	// Simple transform struct for position, rotation, and scale.
	struct Transform
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // Identity quaternion
		glm::vec3 scale = glm::vec3(1.0f);

		// Get model matrix.
		glm::mat4 GetMatrix() const
		{
			const glm::mat4 t = glm::translate(glm::mat4(1.0f), position);
			const glm::mat4 r = glm::toMat4(rotation);
			const glm::mat4 s = glm::scale(glm::mat4(1.0f), scale);
			return t * r * s;
		}

		// Set rotation from Euler angles in degrees.
		void SetRotation(const float pitchDeg, const float yawDeg, const float rollDeg)
		{
			rotation = glm::quat(glm::vec3(
				glm::radians(pitchDeg),
				glm::radians(yawDeg),
				glm::radians(rollDeg)
			));
		}

		// Get Euler angles in degrees.
		glm::vec3 GetRotation() const
		{
			return glm::degrees(glm::eulerAngles(rotation));
		}
	};
}