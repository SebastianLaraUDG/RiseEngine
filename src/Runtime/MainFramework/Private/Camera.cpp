#include <Runtime/MainFramework/Public/Camera.h>
#include <vendor/nlohmann/Json/json.hpp>
#include <fstream>

Camera::Camera(const std::filesystem::path& jsonPath)
{
	using json = nlohmann::json;

	std::ifstream file(jsonPath);
	if (file.is_open())
	{
		json j;
		file >> j;

		Vector3 startingLocation;
		startingLocation.X = j["startingLocation"]["x"];
		startingLocation.Y = j["startingLocation"]["y"];
		startingLocation.Z = j["startingLocation"]["z"];

		Vector3 startingRotation;
		startingRotation.X = j["startingRotation"]["roll"];
		startingRotation.Y = j["startingRotation"]["pitch"];
		startingRotation.Z = j["startingRotation"]["yaw"];

		spaceComponent_->SetLocation(startingLocation);
		spaceComponent_->SetRotation(startingRotation);
	}
	/*
	* Ok here is my idea.
	This constructor will read from a file to get the:
	*starting location
	* and the starting rotaion.
	The file approach will be taken to avoid relying on
	compilation times and improve iteration speed.
	*/
}

// Controls

// WASD
// Q - Going down
// E - Going up
// Mouse - Rotate camera (yaw and pitch)
// Mouse wheel will increase/decrease movement speed.
// N and M keys to modify roll values (DEBUG/TESTING only, then remove).

// TODO: implement time.