#include <Runtime/MainFramework/Public/Camera.h>
#include <vendor/nlohmann/Json/json.hpp>
#include <fstream>

Camera::Camera(const std::filesystem::path& jsonPath) : cameraTarget_(Vector3::ZeroVector()/*TODO: TEMPORAL. This is to look at the origin.*/)
{
	using json = nlohmann::json;

	std::ifstream file(jsonPath);
	if (file.is_open())
	{
		json j;
		file >> j;

		// Load starting location.
		Vector3 startingLocation{};
		startingLocation.X = j["startingLocation"]["x"];
		startingLocation.Y = j["startingLocation"]["y"];
		startingLocation.Z = j["startingLocation"]["z"];

		// Load starting rotation.
		Vector3 startingRotation{};
		startingRotation.X = j["startingRotation"]["roll"];
		startingRotation.Y = j["startingRotation"]["pitch"];
		startingRotation.Z = j["startingRotation"]["yaw"];

		spaceComponent_->SetLocation(startingLocation);
		spaceComponent_->SetRotation(startingRotation);
	}
	else
	{
		std::cout << "LOG | ERROR. FILE COULD NOT BE FOUND: " << jsonPath << "\n";
	}

	/*
	*  For the view matrix's coordinate system we want its z-axis to be
	* positive and because by convention (in OpenGL) the camera points
	* towards the negative z-axis we want to negate the direction vector.
	* If we switch the subtraction order around we now get a vector pointing towards
	* the camera's positive z-axis:
	*/
	cameraDirection_ = (spaceComponent_->GetLocation() - cameraTarget_).GetNormal();

	// TODO: unit tests for cross products to equal world unit direction vector.
	Matrix4f view{};
		/*
		* Ok here is my idea.
		This constructor will read from a file to get the:
		*starting location
		* and the starting rotaion.
		The file approach will be taken to avoid relying on
		compilation times and improve iteration speed.
		*/
};
// Controls

// WASD
// Q - Going down
// E - Going up
// Mouse - Rotate camera (yaw and pitch)
// Mouse wheel will increase/decrease movement speed.
// N and M keys to modify roll values (DEBUG/TESTING only, then remove).

// TODO: implement time.