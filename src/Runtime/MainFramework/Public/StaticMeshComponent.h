#pragma once
#include "MeshComponent.h"

/**
* @brief Class for all STATIC geometries that can be rendered.
This class is only used for rendering simple shapes like cubes or pyramids for now.
Eventually (I hope), it will be capable of rendering complex meshes with no animation.
*/

class StaticMeshComponent : public MeshComponent
{
public:
	StaticMeshComponent();
	~StaticMeshComponent();
	void Init();
	void DeInit();
};

