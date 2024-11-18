#pragma once
#include <array>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <typeindex>
#include <vector>

enum class ComponentType
{
	PositionComponent,
	MovementComponent,
	SpriteComponent,
	HealthComponent,
	TransformComponent,
	SurvivalComponent
};

struct IComponentHandler
{
	virtual void add_Component(unsigned int entityID) = 0;
	virtual void remove_Component(unsigned int entityID) = 0;
};

template<typename Type>
class ComponentHandler : public IComponentHandler
{
public:

	void add_Component(unsigned int entityID) override
	{
		entityIDtoComponent[entityID] = components.size();
		components.emplace_back();
	}

	void remove_Component(unsigned int entityID) override
	{
		// TODO ADD FUNCTIONALITY
	}

	bool has_Component(unsigned int entityID)
	{
		return entityIDtoComponent.contains(entityID);
	}

	Type& get_Component(unsigned int entityID)
	{
		if (has_Component(entityID)) 
			return components[entityIDtoComponent[entityID]];
		std::string message = "Couldn't get component of type: " + std::string(typeid(Type).name()) + ", For EntityID " + std::to_string(entityID);
		throw std::runtime_error(message);
	}
private:
	std::unordered_map<unsigned int, unsigned int> entityIDtoComponent;
	std::vector<Type> components;
};

class ComponentManager
{
public:
	template<typename Type>
	void add_Component(unsigned int entityID)
	{
		if (!componentHandlers.contains(typeid(Type)))
			componentHandlers[typeid(Type)] = std::make_unique<ComponentHandler<Type>>();
		componentHandlers[typeid(Type)]->add_Component(entityID);
	}

	template<typename Type>
	Type& get_Component(unsigned int entityID)
	{
		return static_cast<ComponentHandler<Type>*>(componentHandlers[typeid(Type)].get())->get_Component(entityID);
	}
private:
	std::unordered_map<std::type_index, std::unique_ptr<IComponentHandler>> componentHandlers;
};

