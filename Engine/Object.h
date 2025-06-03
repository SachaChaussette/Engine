#pragma once
#include "TransformableModifier.h"

class ENGINE_API Object
{

public:
	FORCEINLINE virtual Drawable* GetDrawable() const = 0;
	
public:
	virtual ~Object() {};
};