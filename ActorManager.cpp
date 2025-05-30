#include "ActorManager.h"

ActorManager::~ActorManager()
{
	for (AActor* _actor : allActors)
	{
		delete _actor;
	}
}


void ActorManager::BeginPlay()
{
	for (AActor* _actor : allActors)
	{
		_actor->BeginPlay();
	}
}

void ActorManager::Update(const float _deltaTime)
{
	vector<AActor*> _garbage;

	for (AActor* _actor : allActors)
	{
		if (_actor->IsActive())
		{
			_actor->Tick(_deltaTime);
		}

		if (_actor->IsToDelete())
		{
			_garbage.push_back(_actor);
		}
	}

	for (AActor* _actor : _garbage)
	{
		_actor->Deconstruct();
		delete _actor;
	}
}

void ActorManager::BeginDestroy()
{
	for (AActor* _actor : allActors)
	{
		_actor->BeginDestroy();
	}
}