#include "../header/ObjectFactory.h"
#include "../header/ObjectManager.h"
#include "../components/header/TextRenderComponent.h"
#include "../components/header/ImageRenderComponent.h"
#include "../components/header/IntegerRenderComponent.h"
#include "../components/header/PlayerPhysicsComponent.h"
#include "../components/header/AstroidPhysicsComponent.h"
#include "../components/header/InputComponent.h"
#include "../components/header/CollisionComponent.h"
#include "../components/header/AnimationComponent.h"
#include "../components/header/InstantObjectSpawnerComponent.h"
#include "../components/header/TimedObjectSpawnerComponent.h"
#include "../components//header/PlasmaBulletPhysicsComponent.h"
#include "../components//header/MachineGunBulletPhysicsComponent.h"
#include "../components/header/GruntEnemyShipPhysicsComponent.h"
#include "../components/header/AIComponent.h"
#include "../components/header/HealthComponent.h"
#include "../components/header/HealthPackPhysicsComponent.h"
#include "../header/SoundFX.h"
#include "../header/GameObject.h"
#include "../header/mydrawengine.h"
#include "../header/vector2D.h"
#include "../header/ErrorLogger.h"
#include "../header/gamecode.h"
#include "../header/LevelManager.h"
#include "../header/EventDispatcher.h"

ObjectFactory::ObjectFactory()
{
}

std::shared_ptr<GameObject>ObjectFactory::createGameObject(std::wstring objectName) const
{
	std::wstring objectNameLower;
	for (wchar_t c : objectName)
		objectNameLower += std::tolower(c);
	
	if (objectNameLower == L"playership")
		return createPlayerShip();
	
	if (objectNameLower == L"astroid")
		return createAstroid();

	if (objectNameLower == L"expolsion")
		return createExplosion();

	if (objectNameLower == L"plasma_bullet")
		return createPlasmaBullet();

	if (objectNameLower == L"machine_gun_bullet")
		return createMachineGunBullet();

	if (objectNameLower == L"grunt_enemy_ship")
		return createGruntEnemyShip();

	if (objectNameLower == L"smoke")
		return createSmoke();

	if (objectNameLower == L"health_pack")
		return createHealthPack();

	const std::wstring errorMessage = L"Error in object factory, " + objectName + L" is invalid";
	ErrorLogger::Writeln(*errorMessage.c_str());
	return nullptr;
}

std::shared_ptr<LevelManager> ObjectFactory::createLevelManager() const
{
	std::shared_ptr<InstantObjectSpawnerComponent>instantObjectSpawnerComponent =
		std::make_shared<InstantObjectSpawnerComponent>(std::make_shared<ObjectFactory>());
	instantObjectSpawnerComponent->initialise(std::make_shared<ObjectFactory>());
	instantObjectSpawnerComponent->setComponentName(L"instant_object_spawner_component");

	std::shared_ptr<LevelManager>levelManager =
		std::make_shared<LevelManager>();
	levelManager->damage = 0;
	
	std::shared_ptr<TextRenderComponent>scoreTextRenderComponent =
		std::make_shared<TextRenderComponent>();
	scoreTextRenderComponent->initialise(L"Score: ", Vector2D(-1700.0f, 750.0f), MyDrawEngine::WHITE);

	std::shared_ptr<IntegerRenderComponent>scoreValueRenderComponent =
		std::make_shared<IntegerRenderComponent>();
	scoreValueRenderComponent->initialise(0, Vector2D(-1580.0f, 750.0f), MyDrawEngine::CYAN);

	levelManager->initialise(scoreValueRenderComponent, instantObjectSpawnerComponent);

	levelManager->addComponent(instantObjectSpawnerComponent);
	levelManager->addComponent(scoreTextRenderComponent);
	levelManager->addComponent(scoreValueRenderComponent);
	return levelManager;
}

std::shared_ptr<GameObject>ObjectFactory::createPlayerShip() const
{
	std::shared_ptr<GameObject>playerSpaceship =
		std::make_shared<GameObject>(
			std::make_shared<EventDispatcher>(Game::instance.getLevelManager()),
			ObjectType::PLAYER_SHIP);
	playerSpaceship->damage = 100;
	playerSpaceship->scale = 1.0f;

	PictureIndex playerShipPicture = MyDrawEngine::GetInstance()->LoadPicture(L"assets/basic.bmp");
	std::shared_ptr<ImageRenderComponent>playerRenderComponent = 
		std::make_shared<ImageRenderComponent>();
	playerRenderComponent->initialise(playerShipPicture, Vector2D(0.0f, 0.0f), true, true, 0.0f,
	0.0f, true, 0.0f);

	std::shared_ptr<TextRenderComponent> playerDodgeTextRenderComponent = 
		std::make_shared<TextRenderComponent>();
	playerDodgeTextRenderComponent->initialise(L"Dodge Charges:", Vector2D(-1700.0f, 850.0f),
		MyDrawEngine::WHITE);
	playerDodgeTextRenderComponent->setComponentName(L"player_dodge_text_render_component");

	std::shared_ptr<IntegerRenderComponent> playerDodgeValueRenderComponent = 
		std::make_shared<IntegerRenderComponent>();
	playerDodgeValueRenderComponent->initialise(0, Vector2D(-1430.0f, 850.0f), MyDrawEngine::GREEN);
	playerDodgeValueRenderComponent->setComponentName(L"player_dodge_value_render_component");

	std::shared_ptr<TextRenderComponent> playerWeaponSelectionTextRenderComponent =
		std::make_shared<TextRenderComponent>();
	playerWeaponSelectionTextRenderComponent->initialise(L"Selected Weapon:",
		Vector2D(-1700.0f, 800.0f), MyDrawEngine::WHITE);
	playerWeaponSelectionTextRenderComponent->setComponentName(
		L"player_weapon_select_text_render_component");

	PictureIndex plasmaAmmoImage = MyDrawEngine::GetInstance()->LoadPicture(L"assets/plasma.bmp");
	std::shared_ptr<ImageRenderComponent> playerWeaponSelectionImageRenderComponent =
		std::make_shared<ImageRenderComponent>();
	playerWeaponSelectionImageRenderComponent->initialise(plasmaAmmoImage, Vector2D(-1380.0f, 775.0f),
		false, false, 0.0f, 0.0f, false, 1.0f);
	playerWeaponSelectionImageRenderComponent->setComponentName(
		L"player_weapon_selection_image_render_component");

	std::shared_ptr<InstantObjectSpawnerComponent>instantObjectSpawnerComponent = 
		std::make_shared<InstantObjectSpawnerComponent>(std::make_shared<ObjectFactory>());
	instantObjectSpawnerComponent->setComponentName(L"instant_object_spawner_component");

	std::shared_ptr<TimedObjectSpawnerComponent>timedPlasmaBulletObjectSpawnerComponent =
		std::make_shared<TimedObjectSpawnerComponent>(std::make_shared<ObjectFactory>());
	timedPlasmaBulletObjectSpawnerComponent->initialise(0.7f);
	timedPlasmaBulletObjectSpawnerComponent->setComponentName(L"plasma_timed_object_spawner_component");

	std::shared_ptr<TimedObjectSpawnerComponent>timedMachineGunBulletObjectSpawnerComponent =
		std::make_shared<TimedObjectSpawnerComponent>(std::make_shared<ObjectFactory>());
	timedMachineGunBulletObjectSpawnerComponent->initialise(0.1f);
	timedMachineGunBulletObjectSpawnerComponent->setComponentName(
		L"machine_gun_timed_object_spawner_component");

	std::shared_ptr<InputComponent>playerInputComponent = 
		std::make_shared<InputComponent>();
	std::shared_ptr<HealthComponent> playerHealthComponent = std::make_shared<HealthComponent>();
	playerHealthComponent->setComponentName(L"player_health_component");

	std::shared_ptr<TextRenderComponent> playerHealthTextRenderComponent =
		std::make_shared<TextRenderComponent>();
	playerHealthTextRenderComponent->initialise(L"Health:", Vector2D(-1700.0f, 900.0f),
		MyDrawEngine::WHITE);
	
	std::shared_ptr<IntegerRenderComponent> playerHealthValueRenderComponent =
		std::make_shared<IntegerRenderComponent>();
	playerHealthValueRenderComponent->initialise(playerHealthComponent->getHealth(), 
		Vector2D(-1580.0f, 900.0f), MyDrawEngine::RED);
	playerHealthValueRenderComponent->setComponentName(L"player_health_value_render_component");

	playerHealthComponent->initialise(playerHealthValueRenderComponent, 100, 100);

	AngledRectangle2D playerCollisionShape;
	playerCollisionShape.SetDimensions(80, 50);
	std::shared_ptr<PlayerPhysicsComponent>playerPhysicsComponent =
		std::make_shared<PlayerPhysicsComponent>(playerCollisionShape);
	playerPhysicsComponent->initialise(playerHealthComponent);

	std::shared_ptr<CollisionComponent>playerCollisionComponent =
		std::make_shared<CollisionComponent>(playerPhysicsComponent, *playerSpaceship);
	playerCollisionComponent->setComponentName(L"collision_component");

	playerSpaceship->addComponent(playerRenderComponent);
	playerSpaceship->addComponent(playerPhysicsComponent);
	playerSpaceship->addComponent(playerInputComponent);
	playerSpaceship->addComponent(playerCollisionComponent);
	playerSpaceship->addComponent(instantObjectSpawnerComponent);
	playerSpaceship->addComponent(timedPlasmaBulletObjectSpawnerComponent);
	playerSpaceship->addComponent(timedMachineGunBulletObjectSpawnerComponent);
	playerSpaceship->addComponent(playerHealthTextRenderComponent);
	playerSpaceship->addComponent(playerHealthValueRenderComponent);
	playerSpaceship->addComponent(playerDodgeTextRenderComponent);
	playerSpaceship->addComponent(playerDodgeValueRenderComponent);
	playerSpaceship->addComponent(playerWeaponSelectionTextRenderComponent);
	playerSpaceship->addComponent(playerWeaponSelectionImageRenderComponent);
	playerSpaceship->addComponent(playerHealthComponent);
	
	return playerSpaceship;
}

std::shared_ptr<GameObject>ObjectFactory::createAstroid() const
{
	const float ASTROID_SCALE = 1.0f;

	std::shared_ptr<GameObject>astroid =
		std::make_shared<GameObject>(
			std::make_shared<EventDispatcher>(Game::instance.getLevelManager()), ObjectType::ASTROID);

	astroid->damage = 100;
	astroid->scale = ASTROID_SCALE;
	
	PictureIndex astroidPicture = MyDrawEngine::GetInstance()->LoadPicture(L"assets/rock4.bmp");
	std::shared_ptr<ImageRenderComponent>astroidRenderComponent = 
		std::make_shared<ImageRenderComponent>();
	astroidRenderComponent->initialise(astroidPicture, Vector2D(0.0f, 0.0f), true, true, 0.0f,
		0.0f, true, 1.0f);

	std::shared_ptr<HealthComponent> astroidHealthComponent = std::make_shared<HealthComponent>();
	astroidHealthComponent->initialise(nullptr, 60, 60);
	astroidHealthComponent->setComponentName(L"astroid_health_component");

	Circle2D astroidCollisionShape = Circle2D();
	std::shared_ptr<AstroidPhysicsComponent>astroidPhysicsComponent = 
		std::make_shared<AstroidPhysicsComponent>(astroidCollisionShape);
	astroidPhysicsComponent->initialise(astroidHealthComponent, 300.0f, 0.3f, -0.5f, ASTROID_SCALE, 
		Vector2D(0.0f, 0.0f));
	astroidPhysicsComponent->setComponentName(L"astroid_physics_component");

	std::shared_ptr<CollisionComponent>astroidCollisionComponent = 
		std::make_shared<CollisionComponent>(astroidPhysicsComponent, *astroid);
	astroidCollisionComponent->setComponentName(L"collision_component");

	std::shared_ptr<InstantObjectSpawnerComponent> astroidInstantObjectSpawnerComponent =
		std::make_shared<InstantObjectSpawnerComponent>();
	astroidInstantObjectSpawnerComponent->initialise(std::make_shared<ObjectFactory>());
	astroidInstantObjectSpawnerComponent->setComponentName(L"astroid_instant_object_spawner_component");

	astroid->addComponent(astroidRenderComponent);
	astroid->addComponent(astroidPhysicsComponent);
	astroid->addComponent(astroidCollisionComponent);
	astroid->addComponent(astroidHealthComponent);
	astroid->addComponent(astroidInstantObjectSpawnerComponent);

	return astroid;
}

std::shared_ptr<GameObject>ObjectFactory::createExplosion() const
{
	Vector2D pos = Vector2D(0.0f, 0.0f);
	
	std::vector<PictureIndex> images;
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/explosion1.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/explosion2.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/explosion3.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/explosion4.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/explosion5.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/explosion6.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/explosion7.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/explosion8.bmp"));

	std::shared_ptr<GameObject>explosion =
		std::make_shared<GameObject>(
			std::make_shared<EventDispatcher>(Game::instance.getLevelManager()), ObjectType::EXPLOSION);
	explosion->position = pos;
	explosion->damage = 0;
	explosion->scale = 1.0f;
	
	std::shared_ptr<ImageRenderComponent>renderComponent = std::make_shared<ImageRenderComponent>();

	std::shared_ptr<AnimationComponent>animationComponent =
		std::make_shared<AnimationComponent>(images, renderComponent);
	animationComponent->setComponentName(L"explosion_animation_component");

	explosion->addComponent(renderComponent);
	explosion->addComponent(animationComponent);
	
	return explosion;
}

std::shared_ptr<GameObject>ObjectFactory::createSmoke() const
{
	Vector2D pos = Vector2D(0.0f, 0.0f);

	std::vector<PictureIndex> images;
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/puff1.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/puff2.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/puff3.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/puff4.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/puff5.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/puff6.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/puff7.bmp"));
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(L"assets/puff8.bmp"));

	std::shared_ptr<GameObject>smoke =
		std::make_shared<GameObject>(
			std::make_shared<EventDispatcher>(Game::instance.getLevelManager()), ObjectType::EXPLOSION);
	smoke->position = pos;
	smoke->damage = 0;
	smoke->scale = 1.0f;

	std::shared_ptr<ImageRenderComponent>renderComponent = std::make_shared<ImageRenderComponent>();

	std::shared_ptr<AnimationComponent>animationComponent =
		std::make_shared<AnimationComponent>(images, renderComponent);
	animationComponent->setComponentName(L"smoke_animation_component");

	smoke->addComponent(renderComponent);
	smoke->addComponent(animationComponent);

	return smoke;
}

std::shared_ptr<GameObject> ObjectFactory::createHealthPack() const
{
	std::shared_ptr<GameObject> healthPack = std::make_shared<GameObject>(
		std::make_shared<EventDispatcher>(Game::instance.getLevelManager()), ObjectType::HEALTH_PACK);
	Vector2D pos = Vector2D(0.0f, 0.0f);
	healthPack->position = pos;
	healthPack->damage = 0;
	healthPack->healthToHeal = 30;
	healthPack->scale = 1.0f;
	healthPack->invincibleOnSpawn = false;

	PictureIndex healthPackImage = MyDrawEngine::GetInstance()->LoadPicture(L"assets/crate1.bmp");
	std::shared_ptr<ImageRenderComponent>renderComponent = std::make_shared<ImageRenderComponent>();
	renderComponent->initialise(healthPackImage, healthPack->position, true, true, 0.0f, 0.0f, true, 
		1.0f);
	Rectangle2D healthPackCollisionShape;
	healthPackCollisionShape.PlaceAt(100, 75, 30, 110);
	std::shared_ptr<HealthPackPhysicsComponent> healthPackPhysicsComponent =
		std::make_shared<HealthPackPhysicsComponent>(healthPackCollisionShape);
	std::shared_ptr<CollisionComponent> healthPackCollisionComponent =
		std::make_shared<CollisionComponent>(healthPackPhysicsComponent, *healthPack);

	healthPack->addComponent(renderComponent);
	healthPack->addComponent(healthPackPhysicsComponent);
	healthPack->addComponent(healthPackCollisionComponent);
	return healthPack;
}

std::shared_ptr<GameObject> ObjectFactory::createPlasmaBullet() const
{
	const float PLASMA_BULLET_SCALE = 0.7f;
	const float PLASMA_BULLET_ANGLE = 0.0f;
	const float PLASMA_BULLET_TRANSPARENCY = 0.0f;

	std::shared_ptr<GameObject>plasmaBullet =
		std::make_shared<GameObject>(
			std::make_shared<EventDispatcher>(Game::instance.getLevelManager()), 
			ObjectType::PLASMA_BULLET);

	plasmaBullet->damage = 35;
	plasmaBullet->invincibleOnSpawn = false;
	plasmaBullet->scale = PLASMA_BULLET_SCALE;

	PictureIndex bulletPicture = MyDrawEngine::GetInstance()->LoadPicture(L"assets/plasma.bmp");
	std::shared_ptr<ImageRenderComponent> renderComponent = 
		std::make_shared<ImageRenderComponent>();
	renderComponent->initialise(bulletPicture, Vector2D(0.0f, 0.0f), true, true,
		PLASMA_BULLET_ANGLE, PLASMA_BULLET_TRANSPARENCY, true, 1.0f);

	std::shared_ptr<HealthComponent> plasmaBulletHealthComponent = std::make_shared<HealthComponent>();
	plasmaBulletHealthComponent->initialise(nullptr, 20, 20);

	Circle2D plasmaBulletCollisionShape = Circle2D();
	std::shared_ptr<PlasmaBulletPhysicsComponent>plasmaBulletPhysicsComponent =
		std::make_shared<PlasmaBulletPhysicsComponent>(plasmaBulletCollisionShape);
	plasmaBulletPhysicsComponent->setComponentName(L"plasma_bullet_physics_component");
	plasmaBulletPhysicsComponent->initialise(plasmaBulletHealthComponent, PLASMA_BULLET_ANGLE, PLASMA_BULLET_SCALE, Vector2D(0.0f, 0.0f));

	std::shared_ptr<CollisionComponent> collisionComponent =
		std::make_shared<CollisionComponent>(plasmaBulletPhysicsComponent, *plasmaBullet);

	

	plasmaBullet->addComponent(plasmaBulletPhysicsComponent);
	plasmaBullet->addComponent(collisionComponent);
	plasmaBullet->addComponent(renderComponent);
	plasmaBullet->addComponent(plasmaBulletHealthComponent);
	return plasmaBullet;
}

std::shared_ptr<GameObject> ObjectFactory::createMachineGunBullet() const
{
	const float MAGINE_GUN_BULLET_SCALE = 2.0f;
	const float MAGINE_GUN_BULLET_ANGLE = 0.0f;
	const float MAGINE_GUN_BULLET_TRANSPARENCY = 0.0f;

	std::shared_ptr<GameObject>machineGunBullet =
		std::make_shared<GameObject>(
			std::make_shared<EventDispatcher>(Game::instance.getLevelManager()),
			ObjectType::MACHINE_GUN_BULLET);

	machineGunBullet->damage = 4;
	machineGunBullet->invincibleOnSpawn = false;
	machineGunBullet->scale = MAGINE_GUN_BULLET_SCALE;

	PictureIndex machineGunBulletPicture = 
		MyDrawEngine::GetInstance()->LoadPicture(L"assets/bullet.bmp");
	std::shared_ptr<ImageRenderComponent>renderComponent =
		std::make_shared<ImageRenderComponent>();
	renderComponent->initialise(machineGunBulletPicture, Vector2D(0.0f, 0.0f), true, true,
		 MAGINE_GUN_BULLET_ANGLE, MAGINE_GUN_BULLET_TRANSPARENCY, true, 1.0f);

	Circle2D machineGunBulletCollisionShape = Circle2D();
	std::shared_ptr<MachineGunBulletPhysicsComponent>machineGunBulletPhysicsComponent =
		std::make_shared<MachineGunBulletPhysicsComponent>(machineGunBulletCollisionShape);
	machineGunBulletPhysicsComponent->setComponentName(L"machine_gun_bullet_physics_component");
	machineGunBulletPhysicsComponent->initialise(MAGINE_GUN_BULLET_ANGLE, MAGINE_GUN_BULLET_SCALE, 
		Vector2D(0.0f, 0.0f));

	std::shared_ptr<CollisionComponent>collisionComponent =
		std::make_shared<CollisionComponent>(machineGunBulletPhysicsComponent, *machineGunBullet);

	machineGunBullet->addComponent(machineGunBulletPhysicsComponent);
	machineGunBullet->addComponent(collisionComponent);
	machineGunBullet->addComponent(renderComponent);

	return machineGunBullet;
}

std::shared_ptr<GameObject> ObjectFactory::createGruntEnemyShip() const
{
	float GRUNT_ENEMY_SHIP_SCALE = 1.0f;

	std::shared_ptr<GameObject> gruntEnemyShip = std::make_shared<GameObject>(
		std::make_shared<EventDispatcher>(Game::instance.getLevelManager()), 
		ObjectType::GRUNT_ENEMY_SHIP
		);
	gruntEnemyShip->angle = rand() % 628 / 100.0f;
	gruntEnemyShip->scale = GRUNT_ENEMY_SHIP_SCALE;
	gruntEnemyShip->damage = 100;
	Vector2D pos;
	Vector2D velocity;
	pos.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
	velocity.setBearing(gruntEnemyShip->angle, rand() % -80 + 80.0f);

	gruntEnemyShip->position = pos;

	PictureIndex gruntShipImage = MyDrawEngine::GetInstance()->LoadPicture(L"assets/ship.bmp");
	std::shared_ptr<ImageRenderComponent> gruntShipImageRenderComponent = 
		std::make_shared<ImageRenderComponent>();
	gruntShipImageRenderComponent->initialise(gruntShipImage, Vector2D(0.0f, 0.0f), true, true, 
		gruntEnemyShip->angle, 0.0f, true, 1.0f);

	std::shared_ptr<InstantObjectSpawnerComponent> instantObjectSpawnerComponent =
		std::make_shared<InstantObjectSpawnerComponent>(std::make_shared<ObjectFactory>());
	instantObjectSpawnerComponent->setComponentName(L"instant_object_spawner_component");

	std::shared_ptr<AIComponent> gruntShipAIComponent = std::make_shared<AIComponent>();
	gruntShipAIComponent->initialise(2.0f, 3.0f);

	std::shared_ptr<HealthComponent> gruntEnemyShipHealthComponent =
		std::make_shared<HealthComponent>();
	gruntEnemyShipHealthComponent->initialise(nullptr, 20, 20);

	Circle2D gruntShipCollisionShape = Circle2D();
	std::shared_ptr<GruntEnemyShipPhysicsComponent> gruntEnemyShipPhysicsComponent =
		std::make_shared<GruntEnemyShipPhysicsComponent>(gruntShipCollisionShape);
	gruntEnemyShipPhysicsComponent->initialise(gruntEnemyShipHealthComponent, 100.0f, 3.0f, -0.4f, 
		gruntEnemyShip->angle, gruntEnemyShip->scale, velocity, gruntShipAIComponent);

	std::shared_ptr<CollisionComponent> gruntEnemyShipCollisionComponent =
		std::make_shared<CollisionComponent>(gruntEnemyShipPhysicsComponent, *gruntEnemyShip);
	gruntEnemyShipCollisionComponent->setComponentName(L"grunt_enemy_collision_component");

	std::shared_ptr<TimedObjectSpawnerComponent> plasmaGunTimedObjectSpawnerComponent =
		std::make_shared<TimedObjectSpawnerComponent>(std::make_shared<ObjectFactory>());
	plasmaGunTimedObjectSpawnerComponent->setComponentName(L"plasma_gun_timed_object_spawner_component");
	plasmaGunTimedObjectSpawnerComponent->initialise(0.7f);

	gruntEnemyShip->addComponent(gruntShipImageRenderComponent);
	gruntEnemyShip->addComponent(gruntEnemyShipPhysicsComponent);
	gruntEnemyShip->addComponent(gruntEnemyShipCollisionComponent);
	gruntEnemyShip->addComponent(instantObjectSpawnerComponent);
	gruntEnemyShip->addComponent(plasmaGunTimedObjectSpawnerComponent);
	gruntEnemyShip->addComponent(gruntShipAIComponent);
	gruntEnemyShip->addComponent(gruntEnemyShipHealthComponent);

	return gruntEnemyShip;
}

ObjectFactory::~ObjectFactory()
{
}
