#pragma once

class EntityComponent
{
public:
	// ~ Begin EntityComponent interface.
	EntityComponent() = default;
	~EntityComponent() {}
	virtual void Update(float deltaTime);
	// ~ End EntityComponent interface.
protected:
private:
};