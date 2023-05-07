#include "pch.h"
#include "Node.h"


Node::Node()
{
	this->coordinate_x = 0;
	this->coordinate_y = 0;
	this->id = 0;
}
Node::Node(const int x, const int y, const int id)
{
	this->coordinate_x = x;
	this->coordinate_y = y;
	this->id = id;
}
int Node::GetID()
{
	return this->id;
}
int Node::GetX()
{
	return this->coordinate_x;
}
int Node::GetY()
{
	return this->coordinate_y;
}
Node::~Node()
{
}
void Node::SetX(int x)
{
	this->coordinate_x = x;
}
void Node::SetY(int y)
{
	this->coordinate_y = y;
}

