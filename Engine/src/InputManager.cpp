#include "InputManager.h"

#include "GLFW/glfw3.h"

#include "InputEvent.h"

InputManager& InputManager::get_Instance()
{
    static InputManager InputInstance;
    return InputInstance;
}

void InputManager::key_Callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	Key keyType = static_cast<Key>(key);

	if (action == GLFW_PRESS)
	{
		get_Instance().KeyPressedMap[keyType] = true;
		get_Instance().KeyHeldDownMap[keyType] = true;
	}
	else if(action == GLFW_RELEASE)
	{
		get_Instance().KeyHeldDownMap[keyType] = false;
		get_Instance().KeyReleasedMap[keyType] = true;
	}
}

void InputManager::mouse_Callback(GLFWwindow* window, int key, int action, int mods)
{
	Key keyType = static_cast<Key>(key);

	if (action == GLFW_PRESS)
	{
		get_Instance().KeyPressedMap[keyType] = true;
		get_Instance().KeyHeldDownMap[keyType] = true;
	}
	else if(action == GLFW_RELEASE)
	{
		get_Instance().KeyReleasedMap[keyType] = true;
		get_Instance().KeyHeldDownMap[keyType] = false;
	}
}

void InputManager::bind_InputEvent(InputEvent* eventPtr, Key keyType, KeyPress keyPressType)
{
	switch (keyPressType)
	{
	case KeyPress::OnPress:
		get_Instance().KeyPressedEvents[keyType].emplace_back(eventPtr);
		break;

	case KeyPress::WhileHeldDown:
		get_Instance().KeyHeldDownEvents[keyType].emplace_back(eventPtr);
		break;

	case KeyPress::OnRelease:
		get_Instance().KeyReleasedEvents[keyType].emplace_back(eventPtr);
		break;

	default:
		break;
	}
}

void InputManager::run_InputEvents()
{
	for (auto& pressedEvents : KeyPressedEvents)
	{
		if (KeyPressedMap[pressedEvents.first] == true)
		{
			for (InputEvent* event : pressedEvents.second)
			{
				if (event != nullptr)
				{
					event->call_Event();
				}
			}
		}
	}

	for (auto& heldEvents : KeyHeldDownEvents)
	{
		if (KeyHeldDownMap[heldEvents.first] == true)
		{
			for (InputEvent* event : heldEvents.second)
			{
				if (event != nullptr)
				{
					event->call_Event();
				}
			}
		}
	}

	for (auto& releasedEvents : KeyReleasedEvents)
	{
		if (KeyReleasedMap[releasedEvents.first] == true)
		{
			for (InputEvent* event : releasedEvents.second)
			{
				if (event != nullptr)
				{
					event->call_Event();
				}
			}
		}
	}
}

void InputManager::reset_InputMap()
{
	for (auto& key : KeyPressedMap)
	{
		key.second = false;
	}
	for (auto& key : KeyReleasedMap)
	{
		key.second = false;
	}
}
