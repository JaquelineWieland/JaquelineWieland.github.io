#pragma once
#include "stdafx.h"

struct Node;

struct Edge
{
	~Edge()
	{
		node1 = nullptr;
		node2 = nullptr;
	}

	float cost;
	Node* node1;
	Node* node2;

	CircleShape debugGeom;
};

struct Node
{
	~Node()
	{ 
		for (auto e : edges) e = nullptr;
	}

	std::vector<Edge*> edges;
	bool accessible;

	CircleShape debugGeom;
};

class Graph
{
public:
	std::vector<Node*> m_pNodes;
	std::vector<Edge*> m_pEdges;
	void Init(int iTileSize, int iLevelWidth, int iLevelHeight);
	void Render(RenderWindow* pWindow);

	Node* FindClosestNode(Vector2f objectPosition);
	void PlaceObstacle(int x, int y, int width, int height);
	void Shutdown();

private:
	float m_iRadius = 10;
	int m_iColumns;
	int m_iRows;

	void buildNodes(int iWidth, int iHeight);
	void buildEdges();
	void makeNodeUnaccessible(int iNode);
	void makeEdgesAroundCornerUnaccessible(int iPositionX, int iPositionY, int iWidth, int iHeight);
};
