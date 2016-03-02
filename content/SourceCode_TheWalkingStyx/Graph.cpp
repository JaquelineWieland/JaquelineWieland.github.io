#include "stdafx.h"
#include "Graph.h"

//TODO: Make a GameObject out of Graph
void Graph::Init(int iTileSize, int iLevelWidth, int iLevelHeight)
{
	m_iRadius = 6;
	m_iColumns = iLevelWidth / iTileSize;
	m_iRows = iLevelHeight / iTileSize;
	buildNodes(iLevelWidth, iLevelHeight);
	buildEdges();
}

void Graph::Render(RenderWindow* pWindow)
{
	// Debug Information
	for (auto node : m_pNodes)
	{
		pWindow->draw(node->debugGeom);
		for (auto edge : node->edges)
			pWindow->draw(edge->debugGeom);
	}
}

Node* Graph::FindClosestNode(Vector2f objectPosition)
{
	Node* tmp = m_pNodes.front();

	for (int i = 1; i < m_pNodes.size(); i++)
	{
		if (m_pNodes[i]->accessible)
		{
			Vector2f distance1 = tmp->debugGeom.getPosition() - objectPosition;
			float dist1 = sqrt(distance1.x * distance1.x + distance1.y * distance1.y);

			Vector2f distance2 = m_pNodes[i]->debugGeom.getPosition() - objectPosition;
			float dist2 = sqrt(distance2.x * distance2.x + distance2.y * distance2.y);

			if (dist2 < dist1)
			{
				tmp = m_pNodes[i];
			}
		}
	}

	return tmp;
}

void Graph::PlaceObstacle(int x, int y, int iWidth, int iHeight)
{
	for (int i = y; i < y + iHeight; i++)
	{
		for (int j = x; j < x + iWidth; j++)
		{
			makeNodeUnaccessible(i * m_iColumns + j);
		}
	}

	makeEdgesAroundCornerUnaccessible(x, y, iWidth, iHeight);
}

void Graph::makeNodeUnaccessible(int iNode)
{
	// Debug Information
	m_pNodes[iNode]->debugGeom.setFillColor(Color::Black);
	m_pNodes[iNode]->accessible = false;

	for (auto e : m_pNodes[iNode]->edges)
	{
		e->cost = std::numeric_limits<float>::max();

		// Debug Information
		e->debugGeom.setFillColor(Color::Transparent);
	}
}

void Graph::makeEdgesAroundCornerUnaccessible(int iPositionX, int iPositionY, int iWidth, int iHeight)
{
	//top left corner
	int idx = iPositionY * m_iColumns + iPositionX;
	if (idx % m_iColumns != 0 && idx >= m_iColumns)	//Node is not at the very left and not at the top
	{
		for (auto e : m_pNodes[idx - 1]->edges)
		{
			if ((e->node1 == m_pNodes[idx - 1] && e->node2 == m_pNodes[idx - m_iColumns]) ||
				(e->node2 == m_pNodes[idx - 1] && e->node1 == m_pNodes[idx - m_iColumns]))		// <-- Node right of corner
			{
				e->cost = std::numeric_limits<float>::max();

				// Debug Information
				e->debugGeom.setFillColor(Color::Transparent);
			}
		}
	}

	//top right corner
	idx = iPositionY * m_iColumns + iPositionX + iWidth - 1;
	if ((idx + 1) % m_iColumns != 0 && idx >= m_iColumns)	//Node is not at the very right and not at the top
	{
		for (auto e : m_pNodes[idx + 1]->edges)
		{
			if ((e->node1 == m_pNodes[idx + 1] && e->node2 == m_pNodes[idx - m_iColumns]) ||
				(e->node2 == m_pNodes[idx + 1] && e->node1 == m_pNodes[idx - m_iColumns]))		// <-- Node right of corner
			{
				e->cost = std::numeric_limits<float>::max();

				// Debug Information
				e->debugGeom.setFillColor(Color::Transparent);
			}
		}
	}

	//bottom left corner
	idx = (iPositionY + iHeight - 1) * m_iColumns + iPositionX;
	if (idx % m_iColumns != 0 && idx < m_pNodes.size() - m_iColumns)	//Node is not at the very left and not at the bottom
	{
		for (auto e : m_pNodes[idx - 1]->edges)
		{
			if ((e->node1 == m_pNodes[idx - 1] && e->node2 == m_pNodes[idx + m_iColumns]) ||
				(e->node2 == m_pNodes[idx - 1] && e->node1 == m_pNodes[idx + m_iColumns]))		// <-- Node right of corner
			{
				e->cost = std::numeric_limits<float>::max();

				// Debug Information
				e->debugGeom.setFillColor(Color::Transparent);
			}
		}
	}

	//bottom right corner
	idx = (iPositionY + iHeight - 1) * m_iColumns + iPositionX + iWidth - 1;
	if ((idx + 1) % m_iColumns != 0 && idx < m_pNodes.size() - m_iColumns)	//Node is not at the very right and not at the bottom
	{
		for (auto e : m_pNodes[idx + m_iColumns]->edges)
		{
			if ((e->node1 == m_pNodes[idx + 1] && e->node2 == m_pNodes[idx + m_iColumns]) ||
				(e->node2 == m_pNodes[idx + 1] && e->node1 == m_pNodes[idx + m_iColumns]))		// <-- Node right of corner
			{
				e->cost = std::numeric_limits<float>::max();

				// Debug Information
				e->debugGeom.setFillColor(Color::Transparent);
			}
		}
	}
}

void Graph::buildNodes(int iWidth, int iHeight)
{
	const Vector2f InitialPos(iWidth / m_iColumns - m_iRadius / 2, iHeight / m_iRows - m_iRadius / 2);
	const Vector2f dist(iWidth / m_iColumns, iHeight / m_iRows);

	for (int y = 0; y < m_iRows; ++y)
	{
		for (int x = 0; x < m_iColumns; ++x)
		{
			Node *node = new Node{};

			// Debug Information
			node->debugGeom.setFillColor(Color::Green);
			node->debugGeom.setRadius(m_iRadius);
			node->debugGeom.setPosition(InitialPos + Vector2f(x * dist.x, y * dist.y));

			node->accessible = true;

			m_pNodes.push_back(node);
		}
	}
}

void Graph::buildEdges()
{
	int tmp = 0;

	auto calcDist = [](Node& a, Node& b) -> float
	{
		Vector2f pos = a.debugGeom.getPosition() - b.debugGeom.getPosition();
		return sqrt(pos.x * pos.x + pos.y * pos.y);
	};

	for (int y = 0; y < m_iRows; ++y)
	{
		for (int x = 0; x < m_iColumns; ++x)
		{
			int idx = y * m_iColumns + x;

			int idxRight = idx + 1;
			int idxLeft = idx - 1;
			int idxTop = (y - 1) * m_iColumns + x;
			int idxBottom = (y + 1) * m_iColumns + x;

			int idxBottomRight = idxBottom + 1;
			int idxTopRight = idxTop + 1;
			int idxBottomLeft = idxBottom - 1;
			int idxTopLeft = idxTop - 1;

			Node* node = m_pNodes[idx];

			//Only Build the Nodes Right, Bottom Right, Bottom and Bottom Left
			//Then push the edge into Node, as well as NodeR, NodeBR, NodeB and NodeBL

			//Nodes with a Top/Bottom Node
			if (idx <= m_iColumns * (m_iRows - 1) - 1)
			{
				Node* nodeB = m_pNodes[idxBottom];
				Edge* edge = new Edge{ calcDist(*node, *nodeB), node, nodeB };

				node->edges.push_back(edge);
				nodeB->edges.push_back(edge);
				tmp++;
				m_pEdges.push_back(edge);
			}

			//Nodes with a Left/Right Node
			if (idx % m_iColumns != m_iColumns - 1)
			{
				Node* nodeR = m_pNodes[idxRight];
				Edge* edge = new Edge{ calcDist(*node, *nodeR), node, nodeR };

				node->edges.push_back(edge);
				nodeR->edges.push_back(edge);
				tmp++;
				m_pEdges.push_back(edge);
			}

			//Nodes with a Top-Left/Bottom-Right Node
			if (idx % m_iColumns != m_iColumns - 1 && idx <= m_iColumns * (m_iRows - 1) - 1)
			{
				Node* nodeBR = m_pNodes[idxBottomRight];
				Edge* edge = new Edge{ calcDist(*node, *nodeBR), node, nodeBR };

				node->edges.push_back(edge);
				nodeBR->edges.push_back(edge);
				tmp++;

				Node* nodeR = m_pNodes[idxRight];
				Node* nodeB = m_pNodes[idxBottom];
				Edge* edge2 = new Edge{ calcDist(*nodeB, *nodeR), nodeB, nodeR };

				nodeB->edges.push_back(edge2);
				nodeR->edges.push_back(edge2);
				tmp++;
				m_pEdges.push_back(edge);
				m_pEdges.push_back(edge2);
			}
		}
	}

	for (auto node : m_pNodes)
		for (auto edge : node->edges)
		{
			Vector2f pos = edge->node1->debugGeom.getPosition() + 0.5f * (edge->node2->debugGeom.getPosition() - edge->node1->debugGeom.getPosition());
			// Debug Information
			edge->debugGeom.setPosition(pos);
			edge->debugGeom.setFillColor(Color::Blue);
			edge->debugGeom.setRadius(m_iRadius* 0.5f);
		}

	std::cout << "Number of Edges:" << tmp << std::endl;
}

void Graph::Shutdown()
{
	for (auto node : m_pNodes) delete node;
	m_pNodes.clear();
	for (auto edge : m_pEdges) delete edge;
	m_pEdges.clear();
}