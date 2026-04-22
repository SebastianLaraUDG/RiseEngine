#pragma once
#include <RiseEngineCore/Core/CoreTypes.hpp>

// Declaracion:
uint32 glCheckError_(const char* file, int line);

// Macro:
#define glCheckError() glCheckError_(__FILE__, __LINE__)
