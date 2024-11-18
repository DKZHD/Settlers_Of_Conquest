#include <exception>
#include <iostream>
#include "Engine.h"
#include "ECS/Components/Components.h"
#include "ECS/Managers/ComponentManager.h"

int main()
{
	try
	{
		Engine::get_Instance().Run();
	}
	catch (std::exception& e)
	{
		std::cout << "Type thrown: "<< typeid(e).name() << ", Message: " << e.what();
		return 0;
	}
	
	return 0;
}
