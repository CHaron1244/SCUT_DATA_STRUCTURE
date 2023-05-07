#pragma once
class Node
{
	int coordinate_x;//�ڵ�����x
	int coordinate_y;//�ڵ�����y
	int id;//�ڵ���
public:
	Node(const int x, const int y, const int id);
	Node();
	int GetX();
	int GetY();
	int GetID();
	void SetX(int x);
	void SetY(int y);
	Node& operator= (const Node& node)
	{
		if (this != &node)
		{
			this->coordinate_x = node.coordinate_x;
			this->coordinate_y = node.coordinate_y;
			this->id = node.id;
		}
		return *this;

	}
	bool operator==(Node& node)
	{
		if (this == &node)
		{
			return true;
		}
		else if (this->coordinate_x == node.coordinate_x && this->coordinate_y == node.coordinate_y && this->id == node.id)
			return true;
		else return false;

	}
	~Node();
};

#pragma once
