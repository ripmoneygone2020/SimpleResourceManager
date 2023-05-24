#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "CommonTypes.h"
#include "Resource.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <unordered_map>
#include <functional>

struct RESOURCE_EQUAL 
{
	bool operator()(const IDENTITY& LI, const IDENTITY& RI) const
	{
		bool IDMatches = LI.ID == RI.ID ||
			             LI.Name == RI.Name;

		return IDMatches;
	}
};

typedef std::unordered_map<IDENTITY, RESOURCE*, HASH_IDENTITY, RESOURCE_EQUAL> RESOURCE_MAP;

struct RESOURCE_MANAGER
{
	STRING RootPath;
	RESOURCE_MAP Resources;
};

bool InitResourceManager(RESOURCE_MANAGER* ResourceManager, const char* RootPath);
void DestroyResourceManager(RESOURCE_MANAGER* ResourceManager);

bool LoadBMP(RESOURCE_MANAGER* RM, const char* FN);
bool LoadJPG(RESOURCE_MANAGER* RM, const char* FN);
bool LoadPNG(RESOURCE_MANAGER* RM, const char* FN);

bool LoadBMP_GPU(RESOURCE_MANAGER* RM, const char* FN, SDL_Renderer* Renderer);
bool LoadJPG_GPU(RESOURCE_MANAGER* RM, const char* FN, SDL_Renderer* Renderer);
bool LoadPNG_GPU(RESOURCE_MANAGER* RM, const char* FN, SDL_Renderer* Renderer);

bool LoadFont(RESOURCE_MANAGER* RM, const char* FN, INT32 S);

#endif
