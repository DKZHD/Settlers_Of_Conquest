#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <glm/matrix.hpp>
struct PositionComponent
{
	glm::vec2 position;
};

struct MovementComponent
{
	glm::vec2 velocity;
};

struct SpriteComponent
{
	std::string SpriteName;
	std::string MaterialName;
};

struct HealthComponent
{
	uint16_t CurrentHealth = 100;
	uint16_t MaxHealth = 100;
};
struct TransformComponent
{
	glm::vec2 rotation;
	glm::vec2 scale;
	glm::mat4 Transform;
};

struct SurvivalComponent
{
	uint8_t Hunger;
	uint8_t Sleep;
	uint8_t Thirst;
	uint8_t Padding;
};
