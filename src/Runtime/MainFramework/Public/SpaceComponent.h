#pragma once
#include "EntityComponent.h"

struct Transform
{
	Vector3 location;
	Vector3 scale;
	Vector3 rotation;

	Transform() : location(Vector3::ZeroVector()), scale(Vector3::OneVector()), rotation(Vector3::ZeroVector()) {}
};

/**
* @brief The SpaceComponent is responsible for storing the transform of the entity,
which includes its position, scale and rotation in the world.
*/
class SpaceComponent : public EntityComponent
{
public:
	SpaceComponent() = default;
	~SpaceComponent() {}
	virtual void Update(float deltaTime) override;

	// Getters for aboslute transforms.
	FORCEINLINE Transform GetTransform() const { return transform_; }
	FORCEINLINE Vector3 GetLocation() const { return transform_.location; }
	FORCEINLINE Vector3 GetScale() const { return transform_.scale; }
	FORCEINLINE Vector3 GetRotation() const { return transform_.rotation; }
protected:
private:
	Transform transform_;
};