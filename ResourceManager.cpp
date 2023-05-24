#include "ResourceManager.h"

inline static STRING BuildPath(RESOURCE_MANAGER* ResourceManager, const char* FolderName, const char* Filename)
{
	STRING Path(ResourceManager->RootPath);

	Path.append(FolderName);
	Path.append(Filename);

	return Path;
}

inline static void AddResource(RESOURCE_MANAGER* ResourceManager, RESOURCE* Resource)
{
	ResourceManager->Resources[Resource->Identity] = Resource;
}

inline static bool LoadFont(RESOURCE_MANAGER* ResourceManager, const char* FolderName, const char* Filename, INT32 Size)
{
	STRING Path = BuildPath(ResourceManager, FolderName, Filename);
	RESOURCE* Resource = NewResource();

	if(Resource)
	{
		FILE_INFO FileInfo { };

		FileInfo.AbsPath = Path;
		FileInfo.Name = Filename;
		FileInfo.Ext = FILE_EXT_TTF;
		// FileInfo.Size = 0;

		InitResource_FONT(Resource, &FileInfo, Size);

		if(Resource->State.Loaded)
		{
			AddResource(ResourceManager, Resource);
			return true;
		}

		free(Resource);
		Resource = 0;
	}

	return false;
}

inline static bool LoadImage(RESOURCE_MANAGER* ResourceManager, const char* Folder, const char* Filename, FILE_EXTENSION Ext, bool HAccel, SDL_Renderer* Renderer)
{
	STRING Path = BuildPath(ResourceManager, Folder, Filename);
	RESOURCE* Resource = NewResource();

	if(Resource) 
	{
		FILE_INFO FileInfo { };

		FileInfo.AbsPath = Path;
		FileInfo.Name = Filename;
		FileInfo.Ext = Ext;

		InitResource_IMAGE(Resource, &FileInfo, HAccel, Renderer);

		if(Resource->State.Loaded)
		{
			AddResource(ResourceManager, Resource);
			return true;
		}

		free(Resource);
		Resource = 0;
	}

	return false;
}

bool InitResourceManager(RESOURCE_MANAGER* RM, const char* RP)
{
	// TODO: Check if root path exists
	// maybe not check it, idk or just create 
	// the directory if it doesn't exit
	// or just fail out if it doesnt
	// idk yet

	RM->RootPath = RP;
	return true;
}

void DestroyResourceManager(RESOURCE_MANAGER* RM)
{
	auto I = std::begin(RM->Resources);
	auto E = std::end(RM->Resources);

	while(I != E)
	{
		LPVOID Data = I->second->Data;

		if(Data)
		{
			switch(I->second->Type)
			{
				case RESOURCE_FONT: 
				{
					FONT* F = (FONT*) I->second->Data;
					TTF_CloseFont(F->Font);

					break;
				}

				case RESOURCE_IMAGE: 
				{
					// IMAGE* IMG = (IMAGE*) I->second->Data;
					// SDL_FreeSurface(IMG->Surface);

					break;
				}
			}

			free(Data);
			Data = 0;
		}

		RESOURCE* R = I->second;

		if(R)
		{
			free(R);
			R = 0;
		}

		I++;
	}
}

bool ResourceLoaded(RESOURCE_MANAGER* RM, const char* FN)
{
	IDENTITY RID { 0, FN };

	BOOL Loaded = RM->Resources.count(RID) > 0;
	return Loaded;
}

bool LoadBMP_GPU(RESOURCE_MANAGER* RM, const char* FN, SDL_Renderer* Renderer)
{
	if(!ResourceLoaded(RM, FN))
		return LoadImage(RM, "\\Images\\", FN, FILE_EXT_BMP, true, Renderer);

	return false;
}

bool LoadJPG_GPU(RESOURCE_MANAGER* RM, const char* FN, SDL_Renderer* Renderer)
{
	if(!ResourceLoaded(RM, FN))
		return LoadImage(RM, "\\Images\\", FN, FILE_EXT_JPG, true, Renderer);

	return false;
}

bool LoadPNG_GPU(RESOURCE_MANAGER* RM, const char* FN, SDL_Renderer* Renderer)
{
	if(!ResourceLoaded(RM, FN))
		return LoadImage(RM, "\\Images\\", FN, FILE_EXT_PNG, true, Renderer);

	return false;
}

bool LoadBMP(RESOURCE_MANAGER* RM, const char* FN)
{
	if(!ResourceLoaded(RM, FN))
		return LoadImage(RM, "\\Images\\", FN, FILE_EXT_BMP, false, nullptr);

	return false;
}

bool LoadJPG(RESOURCE_MANAGER* RM, const char* FN)
{
	if(!ResourceLoaded(RM, FN))
		return LoadImage(RM, "\\Images\\", FN, FILE_EXT_JPG, false, nullptr);

	return false;
}

bool LoadPNG(RESOURCE_MANAGER* RM, const char* FN)
{
	if(!ResourceLoaded(RM, FN))
		return LoadImage(RM, "\\Images\\", FN, FILE_EXT_PNG, false, nullptr);

	return false;
}

bool LoadFont(RESOURCE_MANAGER* RM, const char* FN, INT32 S)
{
	if(!ResourceLoaded(RM, FN))
		return LoadFont(RM, "\\Fonts\\", FN, S);

	return false;
}
