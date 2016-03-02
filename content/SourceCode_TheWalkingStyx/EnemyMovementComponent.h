#pragma once
#include "stdafx.h"
#include "Graph.h"
#include "PhysicManager.h"
#include "EventHeader.h"

struct SightEvent;

struct NodeRecord
{
	Node* pNode;
	NodeRecord* pConnection;
	float fCostSoFar;
	float fEstimatedTotalCost;
};

class EnemyMovementComponent : public IComponent, public EventHandler<EnemyAttractionEvent>
{
public:
	EnemyMovementComponent(int iSightRadius, int iHearingRadius, Graph* pGraph, GameObject* pOwner, RenderWindow* pWindow);
	void Update(float fTime, GameObject* pOwner);
	void Render(GameObject* pOwner);
	void Shutdown();
	void GatherVision(SightEvent e);
	void onEvent(EnemyAttractionEvent* e) override;

private:
	void moveTowardsPlayerLocation(float fTime, GameObject* pOwner);
	void moveIdle(float fTime, GameObject* pOwner);
	NodeRecord* aStar(Node* start, Node* goal);
	NodeRecord* copyRoute(NodeRecord* pRoute);
	void deleteRoute(NodeRecord* pRoute);
	float euklidDistance(Node* a, Node* b);
	float length(Vector2f a);

	int m_iFrameCounter;
	int m_iSightRadius;
	int m_iHearingRadius;
	int m_iIdleMovementRadius;
	bool m_bPlayerIsInSight;
	bool m_bPlayerIsHeard;
	float m_fSpeed;

	bool isAttackFired = false;
	bool isIdleFired = false;

	Graph* m_graph;
	NodeRecord* m_pRoute;

	GameObject* m_pOwner;
	GameObject* m_pPlayer;
	Vector2f m_playerLastSeenOrHeard;

	float m_fIdleMovementTime;
	Vector2f m_idleMovementDirection;
	Vector2f m_pCenterOfMovement;

	CircleShape m_visionDebugGeometry;
	CircleShape m_hearingDebugGeometry;
	CircleShape m_centerOfMovementDebugGeometry;
	RenderWindow* m_pWindow;
};