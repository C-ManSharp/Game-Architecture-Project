#include "../header/InputComponent.h"
#include "../../header/Message.h"
#include "../../commands/header/Command.h"
#include "../../header/myinputs.h"
#include "../../header/GameObject.h"

#include "../../commands/header/MoveForwardCommand.h"
#include "../../commands/header/RotateLeftCommand.h"
#include "../../commands/header/RotateRightCommand.h"
#include "../../commands/header/MoveBackCommand.h"
#include "../../header/SoundFX.h"
#include "../header/InstantObjectSpawnerComponent.h"
#include "../header/TimedObjectSpawnerComponent.h"
#include "../header/AnimationComponent.h"
#include "../header/PlayerPhysicsComponent.h"
#include "../header/IntegerRenderComponent.h"
#include "../header/ImageRenderComponent.h"
#include "../../header/mydrawengine.h"

InputComponent::InputComponent() : moveForwardCommand{ std::make_shared<MoveForwardCommand>() },
	rotateLeftCommand{std::make_shared<RotateLeftCommand>()},
	rotateRightCommand{ std::make_shared<RotateRightCommand>() },
	moveBackCommand{ std::make_shared<MoveBackCommand>()}, commands{}, 
	MAX_SIZE_OF_REVERSE_COMMANDS_ARRAY{ 50 }, moveFowardButtonIsDown{ false }, frameCount{ 0 }, 
	REVERSE_BOOST_RECHARGE_RATE{ 6 }, weapon{ Weapon::PLASMA }
{
}

void InputComponent::update(GameObject& gameObject, float frameTime)
{
	if (MyInputs::GetInstance()->KeyPressed(DIK_1))
	{
		ImageRenderComponent imageRenderComponent;
		std::shared_ptr<ImageRenderComponent> weaponImageRenderComponent = 
			gameObject.getComponentFromClassAndName(imageRenderComponent, 
			L"player_weapon_selection_image_render_component");
		if (weaponImageRenderComponent)
		{
			weaponImageRenderComponent->initialise(L"assets/plasma.bmp", Vector2D(-1380.0f, 775.0f),
				false, false, 0.0f, 0.0f, false, 1.0f);
		}
		weapon = Weapon::PLASMA;
	}

	if (MyInputs::GetInstance()->KeyPressed(DIK_2))
	{
		ImageRenderComponent imageRenderComponent;
		std::shared_ptr<ImageRenderComponent> weaponImageRenderComponent =
			gameObject.getComponentFromClassAndName(imageRenderComponent,
				L"player_weapon_selection_image_render_component");
		if (weaponImageRenderComponent)
		{
			weaponImageRenderComponent->initialise(L"assets/bullet.bmp", Vector2D(-1380.0f, 775.0f),
				false, false, 0.0f, 0.0f, false, 2.0f);
		}
		weapon = Weapon::MACHINE_GUN;
	}

	if (MyInputs::GetInstance()->KeyPressed(DIK_W))
	{
		moveFowardButtonIsDown = true;
		message->commands.push_back(moveForwardCommand);
		spawnJet(gameObject);
		SoundFX::instance.playEngineSound();
	}
	else
	{
		moveFowardButtonIsDown = false;
		SoundFX::instance.stopEngineSound();
	}
	if (MyInputs::GetInstance()->KeyPressed(DIK_A))
	{
		message->commands.push_back(rotateLeftCommand);
	}
		
	if (MyInputs::GetInstance()->KeyPressed(DIK_D))
	{
		message->commands.push_back(rotateRightCommand);
	}

	if(MyInputs::GetInstance()->KeyPressed(DIK_SPACE))
	{
		if (weapon == Weapon::PLASMA)
			shootPlasmaBullet(gameObject);
		else if (weapon == Weapon::MACHINE_GUN)
			shootMachineGunBullet(gameObject);
	}

	if (MyInputs::GetInstance()->KeyPressed(DIK_Z))
	{
		if (!commands.empty())
		{
			message->commands.push_back(commands.back());
			commands.pop_back();
		}
	}
	
	if (commands.size() < MAX_SIZE_OF_REVERSE_COMMANDS_ARRAY && moveFowardButtonIsDown &&
		frameCount == REVERSE_BOOST_RECHARGE_RATE
		)
	{
		commands.push_back(moveBackCommand);
	}
	
	if (frameCount >= REVERSE_BOOST_RECHARGE_RATE)
	{
		frameCount = 0;
	}

	if (gameObject.state == ObjectState::CAN_DELETE)
		SoundFX::instance.stopEngineSound();

	IntegerRenderComponent integerRenderComponent;
	std::shared_ptr<IntegerRenderComponent> dodgeValueRenderComponent =
		gameObject.getComponentFromClassAndName(integerRenderComponent, 
			L"player_dodge_value_render_component");
	if (dodgeValueRenderComponent)
		dodgeValueRenderComponent->updateIntToDraw(commands.size());
	gameObject.sendMessage(message);
	frameCount++;
}

void InputComponent::spawnJet(GameObject& gameObject) const
{
	const float JET_SCALE = 0.3f;
	InstantObjectSpawnerComponent iosc;
	std::shared_ptr<InstantObjectSpawnerComponent>objectSpawnerComponent = 
		gameObject.getComponentFromClassAndName(iosc, L"instant_object_spawner_component");
	
	if (objectSpawnerComponent)
	{
		std::shared_ptr<GameObject>explosion =
			objectSpawnerComponent->createGameObject(L"expolsion");
		explosion->scale = JET_SCALE;
		AnimationComponent animComponent;
		std::shared_ptr<AnimationComponent>explosionAnimationComponent =
			explosion->getComponentFromClass(animComponent);
		if (explosionAnimationComponent)
		{
			Vector2D jetPosition;
			jetPosition.setBearing(gameObject.angle + 3.14f, 50.0f);
			jetPosition += gameObject.position;
			Vector2D jetVelocity;
			jetVelocity.setBearing(gameObject.angle + 3.14f, 500.0f);
			jetVelocity += gameObject.velocity;
			explosionAnimationComponent->initialise(0.4f, 0.1f, jetVelocity);
			explosion->position = jetPosition;
			objectSpawnerComponent->spawnGameObject(explosion);
		}
	}
}

void InputComponent::shootPlasmaBullet(GameObject& gameObject)
{
	TimedObjectSpawnerComponent tosc;
	std::shared_ptr<TimedObjectSpawnerComponent>objectSpawnerComponent =
		gameObject.getComponentFromClassAndName(tosc, L"plasma_timed_object_spawner_component");
	if (objectSpawnerComponent)
		objectSpawnerComponent->spawnPlasmaBullet(gameObject, 70);
}

void InputComponent::shootMachineGunBullet(GameObject& gameObject)
{
	TimedObjectSpawnerComponent tosc;
	std::shared_ptr<TimedObjectSpawnerComponent>objectSpawnerComponent =
		gameObject.getComponentFromClassAndName(tosc, L"machine_gun_timed_object_spawner_component");
	if (objectSpawnerComponent)
		objectSpawnerComponent->spawnMachineGunBullet(gameObject, 70);
}

InputComponent::~InputComponent()
{
}
