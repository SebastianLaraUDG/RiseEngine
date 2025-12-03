#pragma once
#include <RiseEngineCore/Core.h>
#include "vendor/OpenGL/GLEW/include/GL/glew.h"

#if _DEBUG
#include <iostream>
#endif

// Declaracion:
uint glCheckError_(const char* file, int line);

// Macro:
#define glCheckError() glCheckError_(__FILE__, __LINE__)
