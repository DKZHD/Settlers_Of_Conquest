#include "SystemManager.h"
#include "../Systems/Systems.h"

void SystemManager::Init()
{
	systems[0] = std::make_shared<MovementSystem>();
	systems[1] = std::make_shared<SurvivalSystem>();
	systems[2] = std::make_shared<TransformSystem>();
	systems[3] = std::make_shared<HealthSystem>();
}

void SystemManager::update_Systems(float deltaTime)
{
	for(const std::shared_ptr<ISystem>& system : systems)
	{
		system->Update(deltaTime);
	}
}
