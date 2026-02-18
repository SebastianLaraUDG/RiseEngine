#pragma once
#include "RiseEngineCore/Core/CoreCommon.h"

/**
* @brief The EntityComponent class is the base class
for all components that can be attached to an entity.
*/
class EntityComponent
{
public:
	// ~ Begin EntityComponent interface.
	EntityComponent() = default;
	~EntityComponent() {}
	virtual void Update(float deltaTime);
	// ~ End EntityComponent interface.
protected:
private:
};