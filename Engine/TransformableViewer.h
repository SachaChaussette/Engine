#pragma once
#include "CoreMinimal.h"
#include "TransformData.h"

class ENGINE_API ITransformableViewer
{
public:
	FORCEINLINE virtual Vector2f GetOrigin() const = 0;
	FORCEINLINE virtual Vector2f GetLocation() const = 0;
	FORCEINLINE virtual Angle GetRotation() const = 0;
	FORCEINLINE virtual Vector2f GetScale() const = 0;
	FORCEINLINE virtual TransformData GetTransform() const = 0;
};