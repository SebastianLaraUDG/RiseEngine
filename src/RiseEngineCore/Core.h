#pragma once

// Solo soporta Windows 64 bits
#ifdef _WIN64

// Si estamos compilando el motor (RiseEngine.dll)
#ifdef RISE_ENGINE_BUILD_DLL
#define RISE_ENGINE_API __declspec(dllexport)
#else
// Para cualquier proyecto que use el motor (SandboxApp)
#define RISE_ENGINE_API __declspec(dllimport)
#endif

#else
#error RiseEngine only supports Windows 64-bit!
#define RISE_ENGINE_API
#endif

/*
Right clic Project, properties, C/C++, Preprocessor, preprocessor definitions: RE_BUILD_DLL;_DEBUG
*/