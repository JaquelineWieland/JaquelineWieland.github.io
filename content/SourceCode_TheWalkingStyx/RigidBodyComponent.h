#pragma once
#include "stdafx.h"
#include "PhysicManager.h"

struct CollisionEvent;

class RigidBodyComponent : public IComponent
{
public:
	RectangleShape m_debugGeometry;
	RenderWindow* m_pWindow;

	Vector2f* m_pPosition;
	float m_fWidth;
	float m_fHeight;
	bool m_bBlocksVision;

	float m_fMass;
	float m_fInvMass;
	string m_sTypeOf;

	RigidBodyComponent(float mass, float width, float height, bool bBlocksVision, GameObject* pOwner, RenderWindow* window, string type);
	void GatherCollisions(CollisionEvent e);
	void Update(float fTime, GameObject* pOwner);
	void Render(GameObject* pOwner);
	void Shutdown()  override
	{
		m_pWindow = nullptr;
		m_pPosition = nullptr;
	}

private:
	std::vector<CollisionEvent> m_collisions;
	void resolveCollision();
};

