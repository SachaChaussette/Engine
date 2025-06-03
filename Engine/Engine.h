#pragma once
#include "InputManager.h"

class ENGINE_API Engine
{
	RenderWindow window;
	Input::InputManager inputManager;

public:
	Engine();

public:
	void Start();
	void Update();
	void Stop();
};