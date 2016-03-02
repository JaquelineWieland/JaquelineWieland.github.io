#include "stdafx.h"
#include "ComponentHeader.h"
#include "GameObjectManager.h"

RigidBodyComponent::RigidBodyComponent(float fMass, float fWidth, float fHeight, bool bBlocksVision, GameObject* pOwner, RenderWindow* pWindow, string Type)
{
	SetID(pOwner->m_iID);

	m_debugGeometry = RectangleShape(Vector2f(fWidth, fHeight));
	m_debugGeometry.setFillColor(Color::Transparent);
	m_debugGeometry.setOutlineColor(Color::Red);
	m_debugGeometry.setOutlineThickness(1);
	m_pWindow = pWindow;

	m_fMass = fMass;
	if (fMass == 0)
		m_fInvMass = 0;
	else
		m_fInvMass = 1 / fMass;

	m_pPosition = std::addressof(pOwner->m_position);
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_sTypeOf = Type;
	PhysicManager::GetInstance().RegisterRigidBody(this);
}

void RigidBodyComponent::GatherCollisions(CollisionEvent e)
{
	m_collisions.push_back(e);
}

void RigidBodyComponent::resolveCollision()
{
	for (auto e : m_collisions)
	{
		// both bodys are walls
		if (e.body1->m_sTypeOf == "Wall" && e.body2->m_sTypeOf == "Wall")
			return;
		// body1 is a wall
		else if (e.body1->m_sTypeOf == "Wall")
		{
			e.body2->m_pPosition->x -= e.fPenetration * e.normal.x;
			e.body2->m_pPosition->y -= e.fPenetration * e.normal.y;
		}
		//body2 is a wall
		else if (e.body2->m_sTypeOf == "Wall")
		{
			e.body1->m_pPosition->x += e.fPenetration * e.normal.x;
			e.body1->m_pPosition->y += e.fPenetration * e.normal.y;
		}
		// no body is a wall
		else
		{
			if (e.body1->m_sTypeOf == "Player" && e.body2->m_sTypeOf == "Vase" || e.body2->m_sTypeOf == "Player" && e.body1->m_sTypeOf == "Vase")
			{

				if (e.body1->m_sTypeOf == "Vase")
				{
					ObjectSpriteChangeEvent setBrokenVase(this, "BrokenVaseSprite", e.body1->GetID());
					EventBus::FireEvent(setBrokenVase);

					EnemyAttractionEvent soundAttraction(this, *e.body1->m_pPosition, e.body1->GetID());
					EventBus::FireEvent(soundAttraction);
				}
				if (e.body2->m_sTypeOf == "Vase")
				{
					ObjectSpriteChangeEvent setBrokenVase(this, "BrokenVaseSprite", e.body2->GetID());
					EventBus::FireEvent(setBrokenVase);
					EnemyAttractionEvent soundAttraction(this, *e.body2->m_pPosition, e.body2->GetID());
					EventBus::FireEvent(soundAttraction);
				}

			}
			if (e.body1->m_sTypeOf == "Player" && e.body2->m_sTypeOf == "Enemy")
			{
				PlayerDamageEvent dmgEvent(this, 20, e.body1->GetID()); //InstantDeath
				EventBus::FireEvent(dmgEvent);
			}
			else if (e.body2->m_sTypeOf == "Player" && e.body1->m_sTypeOf == "Enemy")
			{
				PlayerDamageEvent dmgEvent(this, 20, e.body2->GetID()); //InstantDeath
				EventBus::FireEvent(dmgEvent);
			}
			if (e.body1->m_sTypeOf == "Player" && e.body2->m_sTypeOf == "Goal" || e.body2->m_sTypeOf == "Player" && e.body1->m_sTypeOf == "Goal")
			{
				GameStateChangeEvent successevent(this, "SuccessGameState", false);
				EventBus::FireEvent(successevent);

			}
			//std::cout << "Collision of Object " << e.body1->getID() << " and Object " << e.body2->getID() << std::endl;
		}
	}

	m_collisions.clear();
}

void RigidBodyComponent::Update(float fTime, GameObject* pOwner)
{
	// Walls dont need to be moved
	if (m_fInvMass == 0.f) {
		m_collisions.clear();
		return;
	}

	resolveCollision();
}

void RigidBodyComponent::Render(GameObject* pOwner)
{
	// Debug Information
	/*m_debugGeometry.setPosition(Vector2f(m_pPosition->x, m_pPosition->y));
	m_pWindow->draw(m_debugGeometry);*/
}