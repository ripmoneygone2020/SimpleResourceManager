#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <string>
#include <vector>
#include <cstdint>

typedef int8_t INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;

typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef std::size_t SIZE_T;
typedef std::string STRING;

typedef float FLOAT;
typedef bool BOOL;
typedef void* LPVOID;

struct POSITION 
{
	INT32 X; 
	INT32 Y;
};

struct DIMENSION
{
	INT32 W;
	INT32 H;
};

struct RECT 
{
	INT32 X; INT32 Y;
	INT32 W; INT32 H;
};

struct QUAD 
{
	INT32 A; INT32 B;
	INT32 C; INT32 D;
};

struct COLOR 
{
	UINT8 R; UINT8 G;
	UINT8 B; UINT8 A;
};

typedef POSITION POINT;
typedef QUAD BORDER;
typedef QUAD MARGIN;
typedef QUAD PADDING;

struct STYLE_GLOBALS
{
	COLOR BGCOLOR;
	COLOR FGCOLOR;
	COLOR ACCENTCOLOR;
};

#endif
