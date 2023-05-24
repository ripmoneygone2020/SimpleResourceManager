#include "ResourceTypes.h"

FONT* LoadFont(FILE_INFO* FileInfo, INT32 Size)
{
	FONT* Result = nullptr;

	if(Size > 0)
	{
		TTF_Font* Font = nullptr;
		Font = TTF_OpenFont(FileInfo->AbsPath.c_str(), Size);

		if(Font)
		{
			Result = (FONT*) malloc(sizeof(FONT));

			if(Result)
			{
				MEMSET(Result, 0, sizeof(FONT));

				Result->Font = Font;
				Result->Size = Size;
			}
		}
	}

	return Result;
}

bool GPULoad(SDL_Texture** GPUTex, SDL_Surface* Surface, SDL_Renderer* Renderer)
{
	SDL_Texture* Texture = 0;
	Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

	if(Texture)
	{
		*GPUTex = Texture;
		return true;
	}

	return false;
}

IMAGE* LoadImage(FILE_INFO* FileInfo, bool HAccel, SDL_Renderer* Renderer)
{
	IMAGE* Result = nullptr;
	SDL_Surface* Surface = nullptr;

	Surface = IMG_Load(FileInfo->AbsPath.c_str());

	if(Surface)
	{
		Result = (IMAGE*) malloc(sizeof(IMAGE));

		if(Result)
		{
			MEMSET(Result, 0, sizeof(IMAGE));

			Result->Width = Surface->w;
			Result->Height = Surface->h;
			Result->Ext = FileInfo->Ext;

			if(HAccel)
			{
				Result->HAccel = HAccel;

				if(!GPULoad(&Result->Data.Texture, Surface, Renderer))
				{
					free(Result);
					Result = 0;

					// output/display error
					// to error log
				}

				SDL_FreeSurface(Surface);
				Surface = 0;
			}
			else
				Result->Data.Surface = Surface;
		}
	}

	return Result;
}

AUDIO* LoadAudio(FILE_INFO* FileInfo)
{
	return 0;
}
