#pragma once

#include <iostream>

class InputEvent
{
public:
	InputEvent() = default;
	virtual void call_Event() = 0;
};

template <typename Type>
class InputEventCallback : public InputEvent
{
public:
	InputEventCallback(Type* instance, void (Type::* function)()) : Instance(instance), function(function){}

	void call_Event() override
	{
		if (function == nullptr || Instance == nullptr)
		{
			std::cout << "EventCallback is a nullptr" << std::endl;
		}
		else
		{
			(Instance->*function)();
		}
	}
private:
	Type* Instance = nullptr;
	void(Type::* function)() = nullptr;
};

template <typename T>
InputEvent* create_Event(T* instance, void (T::* function)())
{
	return new InputEventCallback(instance, function);
}