#pragma once
#include "ECS/Managers/SystemManager.h"

struct GLFWwindow;

class Engine
{
	// Methods
public:
	static Engine& get_Instance();
	void Run();
private:
	void Init();
	void Tick(float deltaTime);

	Engine() = default;
	Engine(Engine&) = delete;

	// Variables
public:
	GLFWwindow* window;
	SystemManager systemManager;
private:

	//TODO ADD SCENE FUNCTIONALITY

};

