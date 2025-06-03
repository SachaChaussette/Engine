#pragma once
#include "CoreMinimal.h"

template <typename T>
class ENGINE_API Singleton
{
public:
	FORCEINLINE static T& GetInstance()
	{
		static T _instance;
		return _instance;
	}
};