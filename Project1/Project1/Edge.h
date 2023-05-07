#pragma once
#include "Node.h"
class Edge
{
	Node node1;//ߵĶ˽ڵ1
	Node node2;//ߵĶ˽ڵ2
public:
	Edge();
	Edge(Node node1, Node node2);
	Edge& operator=(const Edge& edge)
	{
		if (this != &edge)
		{
			this->node1 = edge.node1;
			this->node2 = edge.node2;
		}
		return *this;

	}
	Node GetNode1() const;
	Node GetNode2();
	~Edge();
};

#pragma once
