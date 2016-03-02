#pragma once
#include "stdafx.h"
#include "ComponentHeader.h"

class RigidBodyComponent;
class EnemyMovementComponent;

struct CollisionEvent
{
	RigidBodyComponent* body1;
	RigidBodyComponent* body2;

	float fPenetration;
	Vector2f normal;
};

struct SightEvent
{
	int iBody1;
	int iBody2;

	bool isInSight;
};

class PhysicManager //Singleton
{
public:
	static PhysicManager& GetInstance();
	void Update();

	void RegisterRigidBody(RigidBodyComponent* pRigidBody);
	void RemoveRigidBody(RigidBodyComponent* c);
	void NotifyRigidBodys();

	void RegisterEnemy(EnemyMovementComponent* pEnemy);
	void RemoveEnemy(EnemyMovementComponent* pEnemy);
	void NotifyEnemy();

	void ReleaseData();

private:
	std::vector<RigidBodyComponent*> m_pRigidBodys;
	std::vector<EnemyMovementComponent*> m_pEnemies;
	std::vector<CollisionEvent> m_collisionEvents;
	std::vector<SightEvent> m_sightEvents;

	PhysicManager() = default;
	~PhysicManager() = default;
	PhysicManager(const PhysicManager& p) = delete;
	PhysicManager& operator= (PhysicManager const&) = delete;

	void findCollisions();
	bool intersect(int iBodyOne, int iBodyTwo, float& fPenetration, Vector2f& normal);
	void findVisibleEnemies();
	bool bodyOneSeesBodyTwo(int iBodyOne, int iBodyTwo);
	
};

