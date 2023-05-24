#ifndef GENERIC_IDENTIFIER_H
#define GENERIC_IDENTIFIER_H

#include "CommonTypes.h"

struct IDENTITY 
{
	UINT64 ID;
	STRING Name;
};

typedef std::hash<STRING> HASH_FUNCTOR;

struct HASH_IDENTITY 
{
	UINT64 operator()(const IDENTITY& Identity) const
	{
		HASH_FUNCTOR Hash { };
		return Hash(Identity.Name);
	}
};

#endif