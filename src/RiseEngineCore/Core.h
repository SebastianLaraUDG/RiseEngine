#pragma once

// Usa _WIN64 que es definido por Visual Studio en configuraciones de 64 bits.
#ifdef _WIN64 
#ifdef RISE_ENGINE_BUILD_DLL
#define RISE_ENGINE_API __declspec(dllexport)
#else
#define RISE_ENGINE_API __declspec(dllimport)
#endif
#else
    // Si no es _WIN64 (p. ej., Linux, macOS, o si no se define), lanzamos el error.
#error RiseEngine only supports Windows!
#define RISE_ENGINE_API 
#endif