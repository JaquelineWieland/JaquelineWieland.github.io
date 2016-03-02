#include "stdafx.h"
#include "ComponentHeader.h"
#include "GameObjectManager.h"

EnemyMovementComponent::EnemyMovementComponent(int iSightRadius, int iHearingRadius, Graph* pGraph, GameObject* pOwner, RenderWindow* pWindow)
{
	m_iFrameCounter = m_iObjectID % 5;
	m_iSightRadius = iSightRadius;
	m_iHearingRadius = iHearingRadius;
	m_iIdleMovementRadius = iSightRadius / 2;
	m_bPlayerIsInSight = false;
	m_bPlayerIsHeard = false;
	m_fSpeed = 100.0f;



	m_graph = pGraph;
	m_pOwner = pOwner;
	m_pPlayer = nullptr;
	m_playerLastSeenOrHeard = Vector2f(0.f, 0.f);

	m_fIdleMovementTime = 0;
	m_pCenterOfMovement = pOwner->m_position;

	// Debug Information
	m_visionDebugGeometry.setRadius(m_iSightRadius);
	m_visionDebugGeometry.setOutlineColor(Color::Red);
	m_visionDebugGeometry.setOutlineThickness(2);
	m_visionDebugGeometry.setFillColor(Color::Transparent);

	// Debug Information
	m_hearingDebugGeometry.setRadius(m_iHearingRadius);
	m_hearingDebugGeometry.setOutlineColor(Color::Yellow);
	m_hearingDebugGeometry.setOutlineThickness(2);
	m_hearingDebugGeometry.setFillColor(Color::Transparent);

	// Debug Information
	m_centerOfMovementDebugGeometry.setRadius(m_iIdleMovementRadius);
	m_centerOfMovementDebugGeometry.setOutlineColor(Color::Green);
	m_centerOfMovementDebugGeometry.setOutlineThickness(2);
	m_centerOfMovementDebugGeometry.setFillColor(Color::Transparent);

	m_pWindow = pWindow;

	PhysicManager::GetInstance().RegisterEnemy(this);
}

void EnemyMovementComponent::Update(float fTime, GameObject* pOwner)
{
	m_pPlayer = GameObjectManager::getInstance().FindGameObjectsByType("Hero")[0];

	if (m_bPlayerIsInSight)
	{
		Vector2f distanceToPlayer = m_pPlayer->m_position - pOwner->m_position;
		if (length(distanceToPlayer) < m_iSightRadius)
			m_playerLastSeenOrHeard = m_pPlayer->m_position;
	}

	if (m_playerLastSeenOrHeard == Vector2f(0.f, 0.f))
	{
		if (!isIdleFired && isAttackFired)
		{
			isAttackFired = false;
			EventBus::FireEvent(EnemyAttackEvent(this, this->GetID(), false));
			isIdleFired = true;
		}
		moveIdle(fTime, pOwner);
	}
	else
	{
		if (!isAttackFired)
		{
			EventBus::FireEvent(EnemyAttackEvent(this, this->GetID(), true));
			isAttackFired = true;
			isIdleFired = false;
		}
		moveTowardsPlayerLocation(fTime, pOwner);
		m_pCenterOfMovement = pOwner->m_position;
	}


	// Debug Information
	m_visionDebugGeometry.setPosition(m_pOwner->m_position - Vector2f(m_iSightRadius, m_iSightRadius));
	m_hearingDebugGeometry.setPosition(m_pOwner->m_position - Vector2f(m_iHearingRadius, m_iHearingRadius));
	m_centerOfMovementDebugGeometry.setPosition(m_pCenterOfMovement - Vector2f(m_iIdleMovementRadius, m_iIdleMovementRadius));
}

void EnemyMovementComponent::Render(GameObject* pOwner)
{
	// Debug Information
	/*m_pWindow->draw(m_centerOfMovementDebugGeometry);
	m_pWindow->draw(m_visionDebugGeometry);
	m_pWindow->draw(m_hearingDebugGeometry);*/
}

void EnemyMovementComponent::Shutdown()
{
	m_graph = nullptr;
	m_pPlayer = nullptr;
	m_pWindow = nullptr;
	deleteRoute(m_pRoute);
}

void EnemyMovementComponent::GatherVision(SightEvent e)
{
	if (e.iBody1 != m_iObjectID && e.iBody2 != m_iObjectID)
		return;
	else if (m_pPlayer != nullptr && (e.iBody1 == m_pPlayer->m_iID || e.iBody2 == m_pPlayer->m_iID))
		m_bPlayerIsInSight = e.isInSight;
}

void EnemyMovementComponent::onEvent(EnemyAttractionEvent* e)
{
	if (length(m_pOwner->m_position - e->m_Position) < m_iHearingRadius)
	{
		if (!m_bPlayerIsInSight || length(m_pOwner->m_position - e->m_Position) > m_iSightRadius)
		{
			Node* pClosestNodeToEnemy = m_graph->FindClosestNode(m_pOwner->m_position);
			Node* pClosestNodeToGadget = m_graph->FindClosestNode(e->m_Position);
			if (pClosestNodeToEnemy != pClosestNodeToGadget)
			{
				deleteRoute(m_pRoute);
				m_pRoute = aStar(pClosestNodeToGadget, pClosestNodeToEnemy)->pConnection;
			}
			m_playerLastSeenOrHeard = e->m_Position;
		}
	}
}

void EnemyMovementComponent::moveTowardsPlayerLocation(float fTime, GameObject* pOwner)
{
	Vector2f distanceToPlayer = m_pPlayer->m_position - pOwner->m_position;
	float distanceToPlayerLength = length(distanceToPlayer);

	// player is in sight and within sightradius
	// means there is no obstacle in between enemy and player and enemy can move directly towards player
	if (m_bPlayerIsInSight && distanceToPlayerLength < m_iSightRadius)
	{
		m_playerLastSeenOrHeard = m_pPlayer->m_position;

		if (distanceToPlayerLength > 4)
		{
			Vector2f directionToPlayer = distanceToPlayer / distanceToPlayerLength;
			pOwner->m_position += directionToPlayer * m_fSpeed * fTime;
		}
		else
			pOwner->m_position = m_pPlayer->m_position;

		deleteRoute(m_pRoute);
	}
	// enemy lost sight of player or just heard him
	// therefore he has to find a route to his last seen/heard position
	else
	{
		if (m_pRoute == nullptr || m_iFrameCounter == 0)
		{
			Node* pClosestNodeToEnemy = m_graph->FindClosestNode(pOwner->m_position);
			pClosestNodeToEnemy->debugGeom.setFillColor(Color::Red);

			Node* pClosestNodeToLastSeenPosition = m_graph->FindClosestNode(m_playerLastSeenOrHeard);
			pClosestNodeToLastSeenPosition->debugGeom.setFillColor(Color::Magenta);

			if (pClosestNodeToEnemy != pClosestNodeToLastSeenPosition)
			{
				deleteRoute(m_pRoute);
				m_pRoute = aStar(pClosestNodeToLastSeenPosition, pClosestNodeToEnemy)->pConnection;
			}
			else
			{
				pOwner->m_position = m_playerLastSeenOrHeard;
				m_playerLastSeenOrHeard = Vector2f(0.f, 0.f);
			}
		}

		if (m_playerLastSeenOrHeard != Vector2f(0.f, 0.f))
		{
			Vector2f direction = m_pRoute->pNode->debugGeom.getPosition() - pOwner->m_position;

			// if enemy is close enough to node, he switches to the next Node
			if (length(direction) < 20)
			{
				// this Node is the last one, so he has to stop moving
				if (m_pRoute->pConnection == nullptr)
				{
					pOwner->m_position = m_playerLastSeenOrHeard;
					m_playerLastSeenOrHeard = Vector2f(0.f, 0.f);

					// might cause an Exception, definetly causes memory leaks if not called
					//delete m_pRoute;
				}
				else
				{
					// might cause an Exception, definetly causes memory leaks if not called
					//NodeRecord* tmp = m_pRoute->pConnection;
					//delete m_pRoute;
					//m_pRoute = tmp;

					m_pRoute = m_pRoute->pConnection;
					direction = m_pRoute->pNode->debugGeom.getPosition() - pOwner->m_position;
				}
			}

			direction = direction / length(direction);
			pOwner->m_position += direction * m_fSpeed * fTime;
		}

		m_iFrameCounter++;
		if (m_iFrameCounter == 5) m_iFrameCounter = 0;
	}
}

void EnemyMovementComponent::moveIdle(float fTime, GameObject* pOwner)
{
	if (m_fIdleMovementTime <= 0)
	{
		m_fIdleMovementTime = (rand() % 10) + 1;
		m_fIdleMovementTime /= 10.f;

		float angle = rand() % 360;
		m_idleMovementDirection = Vector2f(cos(angle * PI / 180), sin(angle * PI / 180));
	}
	else
	{
		m_fIdleMovementTime -= fTime;

		Vector2f distanceFromCenter = m_pCenterOfMovement - (pOwner->m_position + m_idleMovementDirection * (m_fSpeed / 3) * fTime);
		if (length(distanceFromCenter) < m_iIdleMovementRadius)
			pOwner->m_position += m_idleMovementDirection * (m_fSpeed / 3) * fTime / 2.f;
	}
}

NodeRecord* EnemyMovementComponent::aStar(Node* pStart, Node* pGoal)
{
	// custom comparison function for set
	auto comp = [](NodeRecord* a, NodeRecord* b) -> bool { return a->fEstimatedTotalCost < b->fEstimatedTotalCost; };
	std::list<NodeRecord*> open;
	std::list<NodeRecord*> closed;

	auto startRecord = new NodeRecord{ pStart, nullptr, 0.0f , euklidDistance(pStart, pGoal) };
	open.push_back(startRecord);

	NodeRecord* current = nullptr;
	while (open.size())
	{
		current = *open.begin();
		open.remove(current);

		if (current->pNode == pGoal)
			break;

		for (auto e : current->pNode->edges)
		{
			Node* node2;
			if (current->pNode == e->node1)
				node2 = e->node2;
			else
				node2 = e->node1;

			// find node2 in closed and open list
			auto itClosed = find_if(closed.begin(), closed.end(),
				[&node2](NodeRecord* a)->bool
			{ return a->pNode == node2; });
			auto itOpen = find_if(open.begin(), open.end(),
				[&node2](NodeRecord* a)->bool
			{ return a->pNode == node2; });

			float endNodeCost = current->fCostSoFar + e->cost;
			float estimatedEndNodeCost = 0.0f;
			NodeRecord* node2Record;

			// in closed 
			if (itClosed != closed.end())
			{
				node2Record = *itClosed;
				if (node2Record->fCostSoFar <= endNodeCost)
					continue;

				closed.remove(node2Record);
				estimatedEndNodeCost = node2Record->fEstimatedTotalCost - node2Record->fCostSoFar;
			}
			else if (itOpen != open.end())
			{
				node2Record = *itOpen;
				if (node2Record->fCostSoFar <= endNodeCost)
					continue;

				estimatedEndNodeCost = node2Record->fEstimatedTotalCost - node2Record->fCostSoFar;
			}
			else
			{
				node2Record = new NodeRecord{ node2 };
				estimatedEndNodeCost = euklidDistance(node2, pGoal);
			}

			// Update node record
			node2Record->fCostSoFar = endNodeCost;
			node2Record->pConnection = current;
			node2Record->fEstimatedTotalCost = endNodeCost + estimatedEndNodeCost;

			if (find(open.begin(), open.end(), node2Record) == open.end())
				open.push_back(node2Record);

			stable_sort(open.begin(), open.end(), comp);
		}

		open.remove(current);
		closed.push_back(current);
	}

	current = copyRoute(current);

	for (auto nodeRecord : closed)
		delete nodeRecord;
	for (auto nodeRecord : open)
		delete nodeRecord;

	closed.clear();
	open.clear();

	return current;
}

NodeRecord* EnemyMovementComponent::copyRoute(NodeRecord* pRoute)
{
	std::vector<NodeRecord*> pNodeRecordQueue;

	while (pRoute != nullptr)
	{
		NodeRecord* tmp = new NodeRecord();
		tmp->fCostSoFar = pRoute->fCostSoFar;
		tmp->fEstimatedTotalCost = pRoute->fEstimatedTotalCost;
		tmp->pNode = pRoute->pNode;
		pNodeRecordQueue.push_back(tmp);

		pRoute = pRoute->pConnection;
	}

	for (int i = pNodeRecordQueue.size() - 2; i >= 0; i--)
		pNodeRecordQueue[i]->pConnection = pNodeRecordQueue[i + 1];

	NodeRecord* pNewRoute = pNodeRecordQueue[0];

	return pNewRoute;
}

void EnemyMovementComponent::deleteRoute(NodeRecord* pRoute)
{
	std::vector<NodeRecord*> pNodeRecords;

	while (pRoute != nullptr)
	{
		pNodeRecords.push_back(pRoute);
		pRoute = pRoute->pConnection;
	}

	for (auto nodeRecord : pNodeRecords)
	{
		delete nodeRecord;
		nodeRecord = nullptr;
	}

	pNodeRecords.clear();
	m_pRoute = nullptr;
}

float EnemyMovementComponent::euklidDistance(Node* a, Node* b)
{
	Vector2f distance = a->debugGeom.getPosition() - b->debugGeom.getPosition();
	float fDistance = length(distance);
	return fDistance;
}

float EnemyMovementComponent::length(Vector2f a)
{
	float fDistance = sqrt(a.x * a.x + a.y * a.y);
	return fDistance;
}
