#pragma once
#include "RiseEngineCore/Core/CoreCommon.h"
#include "SpaceComponent.h"
#include <vector>

class Entity
{
public:
	// ~ Begin Entity interface.
	Entity();
	~Entity();
	virtual void Update(float deltaTime);
	
	void PrintTransform() const; // TODO: for testing purposes, remove later.
	
	// Create a component of type T and add it to the entity. Returns a pointer to the created component.
	template <typename T>
	T* CreateComponent(); // TODO: internally reserve memory and add to vector of components.

	// ~ End Entity interface.
protected:

private:
	/*
	* TODO: the update() list approach is used for now, but since the elements at the
	* beginning of the list will be updated before the ones at the end, I
	* should implement a different approach like the Double Buffer pattern.
	*/
	std::vector<EntityComponent*> components_; // TODO: for now I will
	// have the components as a vector, but I should
	// look for another structure that better fits according to the needs.
// TODO: also use smart pointers?

	SpaceComponent* spaceComponent_ = nullptr; // TODO: for now I will have the space component as a separate member
};