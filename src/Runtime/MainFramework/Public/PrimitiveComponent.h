#pragma once
#include "SpaceComponent.h"

#define DIMENSION_3 3
#define RGBA_DIMENSION 4

/**
* @brief Collision and abstract rendering.
*/
class PrimitiveComponent : public SpaceComponent
{
public:
	PrimitiveComponent() = default;
	~PrimitiveComponent() {}
};

