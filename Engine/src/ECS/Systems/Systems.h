#pragma once
struct ISystem
{
	virtual void Update(float deltaTime) = 0;
};

struct TransformSystem : public ISystem
{
	void Update(float deltaTime) override;
};
struct MovementSystem : public ISystem
{
	void Update(float deltaTime) override;
};
struct SurvivalSystem : public ISystem
{
	void Update(float deltaTime) override;
};
struct HealthSystem : public ISystem
{
	void Update(float deltaTime) override;
};

