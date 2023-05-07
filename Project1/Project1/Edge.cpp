#include "pch.h"
#include "Edge.h"


Edge::Edge()
{
	this->node1 = Node();
	this->node2 = Node();

}

Edge::Edge(Node node1, Node node2)
{
	this->node1 = node1;
	this->node2 = node2;

}

Edge::~Edge()
{
}
Node Edge::GetNode1() const
{
	return this->node1;
}
Node Edge::GetNode2()
{
	return this->node2;
}
