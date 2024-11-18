#pragma once
#include <array>
#include <memory>

struct ISystem;
class SystemManager
{
public:
	void Init();
	void update_Systems(float deltaTime);
private:

public:

private:
	std::array<std::shared_ptr<ISystem>, 4> systems = {};
};

