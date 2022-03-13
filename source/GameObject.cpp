#include "../header/GameObject.h"
#include "../components/header/Component.h"
#include "../Commands/header/Command.h"
#include "../components/header/CollisionComponent.h"
#include "../components/header/PhysicsComponent.h"
#include "../components/header/ObjectSpawnerComponent.h"
#include "../components/header/AnimationComponent.h"
#include "../header/ErrorLogger.h"

GameObject::GameObject(std::shared_ptr<EventDispatcher> eventDispatcher, ObjectType objectType) :
	position{ Vector2D(0.0f, 0.0f) }, angle{ 0.0f }, components{}, state{ ObjectState::ACTIVE },
	objectType{ objectType }, velocity{ Vector2D() }, damage{ 100 }, eventDispatcher{ eventDispatcher },
	creator{ nullptr }, killer{ nullptr }, invincibleOnSpawn{ true }, scale{ 1.0f }, healthToHeal{ 0 }, 
	creatorObjectType{ ObjectType::UNKOWN }
{
}

GameObject::GameObject(ObjectType objectType) : position{ Vector2D(0.0f, 0.0f) }, angle{ 0.0f }, components{},
state{ ObjectState::ACTIVE }, objectType{ ObjectType::UNKOWN }, velocity{ Vector2D() }, damage{ 100 },
eventDispatcher{ nullptr }, creator{ nullptr }, killer{ nullptr }, invincibleOnSpawn{ true },
scale{ 1.0f }, healthToHeal{ 0 }, creatorObjectType{ objectType }
{
}

GameObject::GameObject() : position{ Vector2D(0.0f, 0.0f) }, angle{ 0.0f }, components{},
state{ ObjectState::ACTIVE }, objectType{ ObjectType::UNKOWN }, velocity{ Vector2D() }, damage{ 100 },
eventDispatcher{ nullptr }, creator{ nullptr }, killer{ nullptr }, invincibleOnSpawn{ true },
scale{ 1.0f }, healthToHeal{ 0 }, creatorObjectType{ ObjectType::UNKOWN }
{
}

void GameObject::addComponent(std::shared_ptr<Component>component)
{
	components.push_back(component);
}

void GameObject::updateComponents(float frameTime)
{
	for (const std::shared_ptr<Component>&COMPONENT : components)
		COMPONENT->update(*this, frameTime);
}

void GameObject::sendMessage(std::shared_ptr<Message>message)
{
	for (const std::shared_ptr<Component>& COMPONENT : components)
		COMPONENT->recieveMessage(message);
}

const ObjectType GameObject::getObjectType() const
{
	return objectType;
}

std::shared_ptr<Component> GameObject::getComponentFromName(std::wstring componentName) const
{
	std::wstring componentNameLower;
	for (wchar_t c : componentName)
		componentNameLower += std::tolower(c);

	for (std::shared_ptr<Component>component : components)
	{
		if (component->getComponentName() == componentName)
			return component;
	}

	const wchar_t* message = L"Could not find ";
	for (wchar_t c : componentName)
		message += c;
	ErrorLogger::Writeln(message);
	return nullptr;
}

GameObject::~GameObject()
{
}
