#pragma once

namespace RiseEngineTypes
{
	// 8 bit
	
	// 0 - 255
	typedef unsigned char uint8;
	typedef unsigned char uchar;
	// -128 - 127
	typedef char int8;
	
	
	// 16 bit

	// 	0 to 65,535
	typedef unsigned short uint16;
	typedef unsigned short ushort;
	// -32,768 to 32,767
	typedef short int16;


	// 32 bit

	// 0 to 4,294,967,295
	typedef unsigned int uint;
	typedef unsigned int uint32;
	// -2,147,483,648 to 2,147,483,647
	typedef int int32;


	// 64 bit

	// 0 to 18,446,744,073,709,551,615
	typedef unsigned long long uint64;
	// -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
	typedef long long int64;
}