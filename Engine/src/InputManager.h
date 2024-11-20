#pragma once

#include <unordered_map>
#include <vector>

#include "InputEvent.h"

enum class Key
{
	W = 87,
	A = 65,
	S = 83,
	D = 68,
	Zero = 48,
	One = 49,
	Two = 50,
	Three = 51,
	Four = 52,
	ESCAPE = 256,
	LMouse = 0,
	RMouse = 1,
};

enum class KeyPress
{
	OnPress,
	OnRelease,
	WhileHeldDown,
	WhileReleased,
};

struct GLFWwindow;

class InputManager
{
public:
	static InputManager& get_Instance();

	static void key_Callback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	static void mouse_Callback(GLFWwindow* window, int key, int action, int mods);

	static void bind_InputEvent(InputEvent* eventPtr, Key keyType, KeyPress keyPressType);
	void run_InputEvents();
	void reset_InputMap();
private:

public:

private:
	std::unordered_map<Key, bool> KeyPressedMap;
	std::unordered_map<Key, bool> KeyHeldDownMap;
	std::unordered_map<Key, bool> KeyReleasedMap;

	std::unordered_map<Key, std::vector<InputEvent*>> KeyPressedEvents;
	std::unordered_map<Key, std::vector<InputEvent*>> KeyHeldDownEvents;
	std::unordered_map<Key, std::vector<InputEvent*>> KeyReleasedEvents;
};
