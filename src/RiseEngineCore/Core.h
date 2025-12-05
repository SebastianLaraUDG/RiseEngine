#pragma once
#include <RiseEngineCore/Types.h>

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


// Data types
using uint8 = RiseEngineTypes::uint8;
using uint16 = RiseEngineTypes::uint16;
using uint32 = RiseEngineTypes::uint32;
using uint64 = RiseEngineTypes::uint64;

using int8 = RiseEngineTypes::int8;
using int16 = RiseEngineTypes::int16;
using int32 = RiseEngineTypes::int32;
using int64 = RiseEngineTypes::int64;

using uint = RiseEngineTypes::uint;
using ushort = RiseEngineTypes::ushort;
using uchar = RiseEngineTypes::uchar;