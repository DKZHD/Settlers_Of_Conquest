#include "Engine.h"

#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Engine& Engine::get_Instance()
{
	static Engine engineInstance;
	return engineInstance;
}

void Engine::Run()
{
	Init();
	float deltatime = 0.f;
	float lastFrame = static_cast<float>(glfwGetTime());
	while(!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltatime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		Tick(deltatime);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void Engine::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MINOR,3);
	glfwWindowHint(GLFW_VERSION_MAJOR,3);
	window = glfwCreateWindow(1920, 1080, "Settlers Of Conquest", nullptr, nullptr);
	if(!window)
	{
		throw std::runtime_error("Window Not Created");
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		throw std::runtime_error("Glad Could not be loaded");
	}
	glViewport(0, 0, 1920, 1080);
	systemManager.Init();
}

void Engine::Tick(float deltaTime)
{
	systemManager.update_Systems(deltaTime);
}
