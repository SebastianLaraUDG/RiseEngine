#include "Runtime/MainFramework/Public/Entity.h"
#include "Runtime/MainFramework/Public/EntityComponent.h"
#include "Runtime/MainFramework/Public/SpaceComponent.h"


#include <iostream> // TODO: remove

Entity::Entity()
{
	spaceComponent_ = CreateComponent<SpaceComponent>();
}

Entity::~Entity()
{
	delete spaceComponent_;
	components_.pop_back(); // Note this only deletes the last element.
}

void Entity::Update(float deltaTime)
{
	//
}

template<typename T>
T* Entity::CreateComponent()
{
	T* component = new T();
	components_.push_back(component);
	return component;
}

void Entity::PrintTransform() const
{
	using std::cout;
	using std::endl;
	cout << "Position: " << spaceComponent_->GetLocation().X << ", " << spaceComponent_->GetLocation().Y << ", " << spaceComponent_->GetLocation().Z << endl;
	cout << "Scale: " << spaceComponent_->GetScale().X << ", " << spaceComponent_->GetScale().Y << ", " << spaceComponent_->GetScale().Z << endl;
	cout << "Rotation: " << spaceComponent_->GetRotation().X << ", " << spaceComponent_->GetRotation().Y << ", " << spaceComponent_->GetRotation().Z << endl;
}