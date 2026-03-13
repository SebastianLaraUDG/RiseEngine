#pragma once
#include "SpaceComponent.h"

#define SIZE_IN_BYTES(_x) sizeof(_x)

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

