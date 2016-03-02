#include "stdafx.h"
#include "PhysicManager.h"


PhysicManager& PhysicManager::GetInstance()
{
	static PhysicManager m_instance;
	return m_instance;
}

void PhysicManager::RegisterRigidBody(RigidBodyComponent* pRigidBody)
{
	m_pRigidBodys.push_back(pRigidBody);
}

void PhysicManager::RemoveRigidBody(RigidBodyComponent* c)
{
	std::vector<RigidBodyComponent*> tmp;

	for (int i = 0; i < m_pRigidBodys.size(); i++)
		if (c != m_pRigidBodys[i])
			tmp.push_back(m_pRigidBodys[i]);

	m_pRigidBodys = tmp;
}

void PhysicManager::NotifyRigidBodys()
{
	// Physic Manager decides who to inform, as the information is stored in the event
	for (auto e : m_collisionEvents)
	{
		e.body1->GatherCollisions(e);
		e.body2->GatherCollisions(e);
	}
}

void PhysicManager::RegisterEnemy(EnemyMovementComponent* pEnemy)
{
	m_pEnemies.push_back(pEnemy);
}

void PhysicManager::RemoveEnemy(EnemyMovementComponent* e)
{
	std::vector<EnemyMovementComponent*> tmp;

	for (int i = 0; i < m_pEnemies.size(); i++)
		if (e != m_pEnemies[i])
			tmp.push_back(m_pEnemies[i]);

	m_pEnemies = tmp;
}

//Notifies all enemies and they decide, if the event is important
void PhysicManager::NotifyEnemy()
{
	for (auto e : m_sightEvents)
	{
		for (auto enemy : m_pEnemies)
			enemy->GatherVision(e);
	}
}

void PhysicManager::Update()
{
	// Collision Detection
	m_collisionEvents.clear();
	findCollisions();
	NotifyRigidBodys();

	// Vision Detection
	m_sightEvents.clear();
	findVisibleEnemies();
	NotifyEnemy();
}

#pragma region Collision Detection
void PhysicManager::findCollisions()
{
	for (int i = 0; i < m_pRigidBodys.size(); i++)
	{
		for (int j = i + 1; j < m_pRigidBodys.size(); j++)
		{
			if (m_pRigidBodys[i]->m_fInvMass == 0 && m_pRigidBodys[j]->m_fInvMass == 0)
				continue;

			float penetration;
			Vector2f normal;
			if (intersect(i, j, penetration, normal))
			{
				CollisionEvent e;

				e.body1 = m_pRigidBodys[i];
				e.body2 = m_pRigidBodys[j];
				e.fPenetration = penetration;
				e.normal = normal;

				m_collisionEvents.push_back(e);
			}
		}
	}
}

bool PhysicManager::intersect(int iBodyOne, int iBodyTwo, float& fPenetration, Vector2f& normal)
{
	float leftFirst = m_pRigidBodys[iBodyOne]->m_pPosition->x;
	float topFirst = m_pRigidBodys[iBodyOne]->m_pPosition->y;
	float widthFirst = m_pRigidBodys[iBodyOne]->m_fWidth;
	float heightFirst = m_pRigidBodys[iBodyOne]->m_fHeight;

	float leftSecond = m_pRigidBodys[iBodyTwo]->m_pPosition->x;
	float topSecond = m_pRigidBodys[iBodyTwo]->m_pPosition->y;
	float widthSecond = m_pRigidBodys[iBodyTwo]->m_fWidth;
	float heightSecond = m_pRigidBodys[iBodyTwo]->m_fHeight;

	// No Collision
	if (leftFirst + widthFirst < leftSecond || leftFirst > leftSecond + widthSecond || topFirst + heightFirst < topSecond || topFirst > topSecond + heightSecond)
		return false;
	// Collision
	else
	{
		float fPenetrationX;
		float fPenetrationY;

		Vector2f normalX;
		Vector2f normalY;

		if (leftFirst < leftSecond)
		{
			fPenetrationX = leftFirst + widthFirst - leftSecond;
			normalX = Vector2f(-1.0f, 0.0f);
		}
		else
		{
			fPenetrationX = leftSecond + widthSecond - leftFirst;
			normalX = Vector2f(1.0f, 0.0f);
		}

		if (topFirst < topSecond)
		{
			fPenetrationY = topFirst + heightFirst - topSecond;
			normalY = Vector2f(0.0f, -1.0f);
		}
		else
		{
			fPenetrationY = topSecond + heightSecond - topFirst;
			normalY = Vector2f(0.0f, 1.0f);
		}

		if (fPenetrationX < fPenetrationY)
		{
			fPenetration = fPenetrationX;
			normal = normalX;
		}
		else
		{
			fPenetration = fPenetrationY;
			normal = normalY;
		}
	}
	return true;
}
#pragma endregion

#pragma region Vision Detection
void PhysicManager::findVisibleEnemies()
{
	//bool playerIsVisible = true;

	for (int i = 0; i < m_pRigidBodys.size(); i++)
	{
		// Walls dont see anybody
		if (m_pRigidBodys[i]->m_fInvMass == 0.f)
			continue;

		for (int j = i + 1; j < m_pRigidBodys.size(); j++)
		{
			// Walls dont see anybody
			if (m_pRigidBodys[j]->m_fInvMass == 0.f)
				continue;

			SightEvent e;
			e.iBody1 = m_pRigidBodys[i]->GetID();
			e.iBody2 = m_pRigidBodys[j]->GetID();
			e.isInSight = bodyOneSeesBodyTwo(i, j);

			m_sightEvents.push_back(e);
		}
	}
}

bool PhysicManager::bodyOneSeesBodyTwo(int iBodyOne, int iBodyTwo)
{
	bool bBodyIsVisible = true;

	// the starting points
	Vector2f BodyOnePos = Vector2f(m_pRigidBodys[iBodyOne]->m_pPosition->x, m_pRigidBodys[iBodyOne]->m_pPosition->y);
	Vector2f BodyTwoPos = Vector2f(m_pRigidBodys[iBodyTwo]->m_pPosition->x, m_pRigidBodys[iBodyTwo]->m_pPosition->y);

	////////////////////////////////////////////////////////////////////////////////////////////////
	////      Careful -> direction components might be 0, so dividing might cause problems      ////
	////////////////////////////////////////////////////////////////////////////////////////////////
	Vector2f direction = BodyTwoPos - BodyOnePos;
	float directionLength = sqrt(direction.x * direction.x + direction.y * direction.y);

	for (int i = 0; i < m_pRigidBodys.size(); i++)
	{
		Vector2f obstaclePos = Vector2f(m_pRigidBodys[i]->m_pPosition->x, m_pRigidBodys[i]->m_pPosition->y);
		float obstacleWidth = m_pRigidBodys[i]->m_fWidth;
		float obstacleHeight = m_pRigidBodys[i]->m_fHeight;

		// A body cant block its own view
		if (i == iBodyOne || i == iBodyTwo)
			continue;

		// If body i is not between bodyOne and bodyTwo, a comparison makes no sense
		if ((obstaclePos.x + obstacleWidth < BodyOnePos.x && obstaclePos.x + obstacleWidth < BodyTwoPos.x) ||	// <-- right side of Body i is to the left of both BodyOne and BodyTwo
			(obstaclePos.x > BodyOnePos.x && obstaclePos.x > BodyTwoPos.x) ||									// <-- left side of Body i is to the right of both BodyOne and BodyTwo
			(obstaclePos.y + obstacleHeight < BodyOnePos.y && obstaclePos.y + obstacleHeight < BodyTwoPos.y) ||	// <-- bottom side of Body i is above both BodyOne and BodyTwo
			(obstaclePos.y > BodyOnePos.y && obstaclePos.y > BodyTwoPos.y))										// <-- top side of Body i is below both BodyOne and BodyTwo
			continue;

		// Above or Under the obstacle
		float offsetLeft = obstaclePos.x - BodyOnePos.x;
		Vector2f intersectionLeft = BodyOnePos + (direction / direction.x) * offsetLeft;

		float offsetRight = obstaclePos.x - BodyOnePos.x + obstacleWidth;
		Vector2f intersectionRight = BodyOnePos + (direction / direction.x) * offsetRight;

		// Left or Right of the Obstacle
		float offsetTop = obstaclePos.y - BodyOnePos.y;
		Vector2f intersectionTop = BodyOnePos + (direction / direction.y) * offsetTop;

		float offsetBottom = obstaclePos.y - BodyOnePos.y + obstacleHeight;
		Vector2f intersectionBottom = BodyOnePos + (direction / direction.y) * offsetBottom;

		if ((intersectionLeft.y > obstaclePos.y && intersectionLeft.y < obstaclePos.y + obstacleHeight) ||		// <-- BodyOne is behind the left side of Body i
			(intersectionRight.y > obstaclePos.y && intersectionRight.y < obstaclePos.y + obstacleHeight) ||	// <-- BodyOne is behind the right side of Body i
			(intersectionTop.x > obstaclePos.x && intersectionTop.x < obstaclePos.x + obstacleWidth) ||			// <-- BodyOne is behind the top side of Body i
			(intersectionBottom.x > obstaclePos.x && intersectionBottom.x < obstaclePos.x + obstacleWidth))		// <-- BodyOne is behind the bottom side of Body i
		{
			bBodyIsVisible = false;
			break;
		}

	}

	return bBodyIsVisible;
}
#pragma endregion

void PhysicManager::ReleaseData()
{
	m_collisionEvents.clear();
	m_pRigidBodys.clear();
	m_pEnemies.clear();
}
