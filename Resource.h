#ifndef RESOURCE_H
#define RESOURCE_H

#include "CommonTypes.h"
#include "Identity.h"
#include "ResourceTypes.h"

enum RESOURCE_TYPE: UINT32
{
	RESOURCE_FONT,
	RESOURCE_AUDIO,
	RESOURCE_IMAGE,
	RESOURCE_ICON
};

struct RESOURCE 
{
	struct RESOURCE_STATE 
	{
		BOOL Dirty;
		BOOL Loaded;
	};

	IDENTITY Identity;
	RESOURCE_STATE State;
	RESOURCE_TYPE Type;
	FILE_INFO FileInfo;
	LPVOID Data;
};

RESOURCE* NewResource();

void InitResource_IMAGE(RESOURCE* Resource, FILE_INFO* FileInfo, bool HAccel, SDL_Renderer* Renderer);
void InitResource_ICON(RESOURCE* Resource, FILE_INFO* FileInfo, bool HAccel, SDL_Renderer* Renderer);
void InitResource_FONT(RESOURCE* Resource, FILE_INFO* FileInfo, INT32 Size);
void InitResource_AUDIO(RESOURCE* Resource, FILE_INFO* FileInfo);

#endif
