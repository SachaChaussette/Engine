#pragma once
#include "Component.h"
#include "Animation.h"

class ENGINE_API UAnimationComponent : public UComponent
{
	Animation* current;
	map<string, Animation*> allAnimations;

	// AnimationPose -> only
	// StateMachine -> auto switch

public:
	FORCEINLINE void SetCurrentAnimation(const string& _name)
	{
		if (!allAnimations.contains(_name)) return;
		current = allAnimations[_name];
	}
	FORCEINLINE void SetCurrentAnimation(Animation* _animation)
	{
		if (!_animation) return;
		current = _animation;
	}
	FORCEINLINE void StartAnimation()
	{
		if (!current) return;

		current->GetOnAnimationEnded() = [&]() 
		{ 
			if (Animation* _animation = current->GetNextAnimation())
			{
				SetCurrentAnimation(_animation);
				StartAnimation();
			}
		};
		current->Start();
	}
	FORCEINLINE void StopAnimation()
	{
		if (!current) return;
		current->Stop();
	}
	FORCEINLINE void SwitchCurrentAnimation(Animation* _animation)
	{
		StopAnimation();
		SetCurrentAnimation(_animation);
		StartAnimation();
	}
	FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
	{
		return new UAnimationComponent(_owner, *this);
	}

public:
	UAnimationComponent(AActor* _owner);
	UAnimationComponent(AActor* _owner, const UAnimationComponent& _other);
	~UAnimationComponent();

	void AddAnimation(Animation* _animation);
	Animation* AddAnimation(const vector<SpriteData>& _spriteData, const float _duration,
		const string& _name, ShapeObject* _shapeObject);
	void AddAnimations(const vector<Animation*>& _animations);
};