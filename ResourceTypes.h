#ifndef RESOURCE_TYPES_H
#define RESOURCE_TYPES_H

#include "CommonTypes.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define MEMSET(DST, VAL, SIZE) std::memset((DST), (VAL), (SIZE))

enum FILE_EXTENSION: UINT32
{
	FILE_EXT_BMP,
	FILE_EXT_JPG,
	FILE_EXT_PNG,

	FILE_EXT_WAV,
	FILE_EXT_TTF,
	FILE_EXT_UNKNOWN
};

struct FILE_INFO 
{
	FILE_EXTENSION Ext;
	STRING AbsPath;
	STRING Name;
	UINT64 Size;
};

struct FONT
{
	TTF_Font* Font;
	INT32 Size;
};

struct IMAGE
{
	INT32 Width; INT32 Height;
	FILE_EXTENSION Ext;
	bool HAccel;

	union {
		SDL_Surface* Surface;
		SDL_Texture* Texture;
	} Data;
};

struct AUDIO 
{
	SDL_AudioSpec* Audio;
	UINT8*		   Buffer;
	UINT32         Length;
};

FONT* LoadFont(FILE_INFO* FileInfo, INT32 Size);
IMAGE* LoadImage(FILE_INFO* FileInfo, bool HAccel, SDL_Renderer* Renderer);
AUDIO* LoadAudio(FILE_INFO* FileInfo);

#endif
