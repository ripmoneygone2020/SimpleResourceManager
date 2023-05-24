#include "Resource.h"

inline static 
UINT64 NextResourceID() 
{
	static UINT64 ID = 0;
	return ++ID;
}

inline static 
void InitResourceIdentity(RESOURCE* Resource, const char* Filename)
{
	Resource->Identity.ID = NextResourceID();
	Resource->Identity.Name = Filename;
}

inline static 
void InitResourceMetaData(RESOURCE* Resource, FILE_INFO* FileInfo, RESOURCE_TYPE Type)
{
	Resource->Type = Type;

	Resource->FileInfo.AbsPath = FileInfo->AbsPath;
	Resource->FileInfo.Name = FileInfo->Name;
	Resource->FileInfo.Ext = FileInfo->Ext;
}

inline static 
void InitResourceState(RESOURCE* Resource, LPVOID Data)
{
	if(Data) 
	{
		Resource->Data = Data;
		Resource->State.Dirty = false;
		Resource->State.Loaded = true;
	}
}

inline static 
void InitResource(RESOURCE* Resource, RESOURCE_TYPE Type, FILE_INFO* FileInfo, LPVOID Data)
{
	InitResourceIdentity(Resource, FileInfo->Name.c_str());
	InitResourceMetaData(Resource, FileInfo, Type);
	InitResourceState(Resource, Data);
}

RESOURCE* NewResource()
{
	RESOURCE* Resource = (RESOURCE*) malloc(sizeof(RESOURCE));

	if(Resource)
		MEMSET(Resource, 0, sizeof(RESOURCE));

	return Resource;
}

void InitResource_ICON(RESOURCE* Resource, FILE_INFO* FileInfo, bool HAccel, SDL_Renderer* Renderer)
{
	InitResource(Resource, RESOURCE_ICON, FileInfo, LoadImage(FileInfo, HAccel, Renderer));
}

void InitResource_IMAGE(RESOURCE* Resource, FILE_INFO* FileInfo, bool HAccel, SDL_Renderer* Renderer)
{
	InitResource(Resource, RESOURCE_IMAGE, FileInfo, LoadImage(FileInfo, HAccel, Renderer));
}

void InitResource_FONT(RESOURCE* Resource, FILE_INFO* FileInfo, INT32 Size)
{
	InitResource(Resource, RESOURCE_FONT, FileInfo, LoadFont(FileInfo, Size));
}

void InitResource_AUDIO(RESOURCE* Resource, FILE_INFO* FileInfo)
{
	// TODO(): IMPLEMENT THIS FUNCTION
	// InitResource(Resource, RESOURCE_AUDIO, AbsPath, Filename, Make);
}
