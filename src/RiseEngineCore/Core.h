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
typedef RiseEngineTypes::uint8	uint8;
typedef RiseEngineTypes::uint16	uint16;
typedef RiseEngineTypes::uint32	uint32;
typedef RiseEngineTypes::uint64	uint64;

typedef RiseEngineTypes::int8	int8;
typedef RiseEngineTypes::int16	int16;
typedef RiseEngineTypes::int32	int32;
typedef RiseEngineTypes::int64	int64;

typedef RiseEngineTypes::uint	uint;
typedef RiseEngineTypes::ushort	ushort;
typedef RiseEngineTypes::uchar	uchar;


// Forward declaration of concrete types.
// TODO: move this to its own file.
#include <RiseEngineCore/Math/RiseMath.h>
namespace RiseEngine::Math
{
	template<typename T> struct TVector;
}

using Vector3 = RiseEngine::Math::TVector<double>;
using Vector3f = RiseEngine::Math::TVector<float>;
