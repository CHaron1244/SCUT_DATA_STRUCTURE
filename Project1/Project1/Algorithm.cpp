#pragma once
#include "pch.h"
#include "MYAlgorithm.h"
extern vector<Node> NodeArray;
extern vector<Edge> EdgeArray;
int max(int x, int y)
{
	return x > y ? x : y;
}
int min(int x, int y)
{
	return x > y ? y : x;
}
double mult(Node a, Node b, Node c)
{
	return (a.GetX() - c.GetX()) * (b.GetY() - c.GetY()) - (b.GetX() - c.GetX()) * (a.GetY() - c.GetY());
}


//************************************
// Method:    intersect
// FullName:  intersect
// Access:    public 
// Returns:   bool
// Qualifier:aa,��bbΪһ���߶����˵㣬cc��ddΪ��һ���߶ε����˵� �ཻ����true, ���ཻ����false
// Parameter: Node aa
// Parameter: Node bb
// Parameter: Node cc
// Parameter: Node dd
//************************************
bool intersect(Node aa, Node bb, Node cc, Node dd)
{
	if (max(aa.GetX(), bb.GetX()) < min(cc.GetX(), dd.GetX()))
	{
		return false;
	}
	if (max(aa.GetY(), bb.GetY()) < min(cc.GetY(), dd.GetY()))
	{
		return false;
	}
	if (max(cc.GetX(), dd.GetX()) < min(aa.GetX(), bb.GetX()))
	{
		return false;
	}
	if (max(cc.GetY(), dd.GetY()) < min(aa.GetY(), bb.GetY()))
	{
		return false;
	}
	if (mult(cc, bb, aa) * mult(bb, dd, aa) < 0)
	{
		return false;
	}
	if (mult(aa, dd, cc) * mult(dd, bb, cc) < 0)
	{
		return false;
	}
	return true;
}
//���׾����x������
double determinant(double v1, double v2, double v3, double v4)  // ����ʽ
{
	return (v1 * v3 - v2 * v4);
}
//�ж�������(�߶�)�Ƿ��ཻ ��-����true ��-����false
bool IsIntersect(Edge edge1, Edge edge2)
{
	Node a, b, c, d;
	a = edge1.GetNode1();
	b = edge1.GetNode2();
	c = edge2.GetNode1();
	d = edge2.GetNode2();
	return intersect(a, b, c, d);

}


//�жϽڵ�node,�Ƿ���node1��node2���߶��� ��-����1 ��-����0
const int on_segment(Node node, Node& node1, Node& node2)
{
	int x1 = node1.GetX();
	int x2 = node2.GetX();
	int y1 = node1.GetY();
	int y2 = node2.GetY();
	double max = x1 > x2 ? x1 : x2;
	double min = x1 < x2 ? x1 : x2;
	double max1 = y1 > y2 ? y1 : y2;
	double min1 = y1 < y2 ? y1 : y2;
	if (node.GetX() >= min && node.GetX() <= max &&
		node.GetY() >= min1 && node.GetY() <= max1)
		return 1;
	else
		return 0;
}
//�ж��±��Ƿ������еı��ཻ����ȥ���ڵıߣ���-����true ��-����false
bool  IsEdgeIntersectedEdgeArray(Edge& edge)
{
	Node node1, node2;//��ȡ���������ڵ�
	Edge Aedge;//������ȡ���ı�
	Node edge_node1, edge_node2;
	edge_node1 = edge.GetNode1();
	edge_node2 = edge.GetNode2();
	vector<Edge>::const_iterator iterator = EdgeArray.begin();
	for (; iterator != EdgeArray.end(); ++iterator)
	{
		Aedge = (*iterator);
		node1 = Aedge.GetNode1();
		node2 = Aedge.GetNode2();
		//�����������ͬ���Ľڵ㣬��ֱ������
		if (node1 == edge_node1 || node1 == edge_node2 || node2 == edge_node1 || node2 == edge_node2)
			continue;
		if (IsIntersect(edge, Aedge) == true)
			return true;
	}
	return false;
}

//************************************
// Method:    IsEdgeIntersectedEdgeArray
// FullName:  IsEdgeIntersectedEdgeArray
// Access:    public 
// Returns:   bool
// Qualifier:���ݵ�ǰ�ڵ���½ڵ�����꣬�ж����߹��ɵ��±��Ƿ�������еı��ཻ
// Parameter: Node cur_node ��ǰ�ڵ�
// Parameter: Node new_node �½ڵ�
//************************************
bool  IsEdgeIntersectedEdgeArray(Node cur_node, Node new_node)
{
	Edge edge(cur_node, new_node);
	Edge Aedge;//������ȡ���ı�
	 //�����δ�бߣ��򷵻�false
	if (EdgeArray.size() == 0)
		return false;
	vector<Edge>::const_iterator iterator = EdgeArray.begin();
	for (; iterator != EdgeArray.end(); ++iterator)
	{
		Aedge = (*iterator);
		//����ɽڵ��Ǳߵ�����һ���ڵ㣬����Ҫ�жϣ�ֱ����һ��ѭ��
		if (Aedge.GetNode1() == cur_node || Aedge.GetNode2() == cur_node)
			continue;
		if (IsIntersect(edge, Aedge) == true)
			return true;
	}
	return false;
}
//�жϽڵ��Ƿ����Ѵ�ߵ�����һ������ ��-����true ��-����false
bool IsNodeInEdgeArray(const Node& node)
{
	Node node1, node2;//��ȡ���������ڵ�
	Edge edge;//������ȡ���ı�
	int Counts = 0;
	//�����δ�бߣ��򷵻�false
	if (EdgeArray.size() == 0)
		return false;
	//���ڵ������б߽����ж��Ƿ����߶���
	vector<Edge>::const_iterator iterator = EdgeArray.begin();
	for (; iterator != EdgeArray.end(); ++iterator)
	{
		edge = (*iterator);
		node1 = edge.GetNode1();
		node2 = edge.GetNode2();
		Counts += on_segment(node, node1, node2);
	}
	if (Counts == 0)
		return false;
	else
		return true;
}
//************************************
// Method:    RandomCreatFunc
// FullName:  RandomCreatFunc
// Access:    public 
// Returns:   int
// Qualifier: �����������������
// Parameter: int interval_min ������ֵ
// Parameter: int interval_max ������ֵ
//************************************
int RandomCreatFunc(int interval_min, int interval_max)
{
	if (interval_min >= interval_max)
		return INT_MAX;
	//����ֵ��ͨ�� random_device ���͵ĺ������� rd ��õġ�
	//ÿһ�� rd() ���ö��᷵�ز�ͬ��ֵ�������������ʵ�ֵ� random_devic �Ƿ�ȷ���Եģ�����ÿ��ִ���������� rd() ���������ͬ�����С�
	random_device rd;
	default_random_engine e{ rd() };
	int random_num = 0;
	//��������������������3�������min<0&&max>0 ��max<0��min>0
	if (interval_min >= 0)//min>0�����
	{
		uniform_int_distribution<unsigned> a(interval_min, interval_max);
		random_num = a(e);
	}
	else if (interval_max > 0)//min<0&&max>0 �����
	{
		uniform_int_distribution<unsigned> a(0, -interval_min);
		random_num = a(e);
		random_num = -random_num;
		uniform_int_distribution<unsigned> b(0, 10);
		if (b(e) % 2 == 0)
		{
			uniform_int_distribution<unsigned> c(0, interval_max);
			random_num = c(e);
		}
	}
	else//max<0�����
	{
		uniform_int_distribution<unsigned> a(-interval_max, -interval_min);
		random_num = a(e);
		random_num = -random_num;
	}
	return random_num;

}
//************************************
// Method:    RandomArray
// FullName:  RandomArray
// Access:    public 
// Returns:   void
// Qualifier:����������� ��������齫���ı�Ϊ�������
// Parameter: int * arr ���������
// Parameter: int Amounts �����С
//************************************
void RandomArray(int* arr, int Amounts)
{
	for (int i = 0; i < Amounts; i++)
		arr[i] = 0;
	int count = 0;		//������
	while (count < Amounts)
	{
		int val = RandomCreatFunc(0, Amounts - 1);//���ȷ���±�
		if (!arr[val])
		{
			arr[val] = count + 1;
			++count;
		}
	}
}
//************************************
// Method:    Distance
// FullName:  Distance
// Access:    public 
// Returns:   double
// Qualifier:�������ڵ�֮��ľ���
// Parameter: Node a
// Parameter: Node b
//************************************
double Distance(Node a, Node b)
{
	return ((a.GetX() - b.GetX()) * (a.GetX() - b.GetX()) + (a.GetY() - b.GetY()) * (a.GetY() - b.GetY()));
}
//************************************
// Method:    IsNodeKeepAwayFromNodeArray
// FullName:  IsNodeKeepAwayFromNodeArray
// Access:    public 
// Returns:   bool
// Qualifier:�жϽڵ��Ƿ�Զ�����еĽڵ�
// Parameter: Node node �ڵ�
// Parameter: int min_distance �������Сֵ
//************************************
bool IsNodeKeepAwayFromNodeArray(Node node, int min_distance)
{
	Node node_choose;
	vector<Node>::const_iterator iter = NodeArray.begin();
	for (; iter != NodeArray.end(); ++iter)
	{
		node_choose = (*iter);
		if (Distance(node, node_choose) < min_distance)
			return false;
	}
	return true;
}
bool AddEdgeToGraph()
{
	vector<Edge> edge_for_add;
	vector<Node>::const_iterator ite1 = NodeArray.begin();
	for (; ite1 != NodeArray.end(); ++ite1)
	{
		vector<Node>::const_iterator ite2 = NodeArray.begin();
		for (; ite2 != NodeArray.end(); ++ite2)
		{
			if (ite1 != ite2 && IsNodeConnected(*ite1, *ite2) == false)
			{
				Edge newEdge(*ite1, *ite2);
				if (IsEdgeIntersectedEdgeArray(newEdge) == false)
					edge_for_add.push_back(newEdge);
			}

		}
	}

	if (edge_for_add.size() == 0) return false;//����Ҳ�������Ҫ��ıߣ��򷵻�false
	int choose_id;
	if (edge_for_add.size() == 1)
		choose_id = 0;
	else
		choose_id = RandomCreatFunc(0, edge_for_add.size() - 1);
	Edge getEdge = edge_for_add.at(choose_id);
	EdgeArray.push_back(getEdge);
	return true;
}
//************************************
// Method:    CreatNewNodeX_Y
// FullName:  CreatNewNodeX_Y
// Access:    public 
// Returns:   void
// Qualifier:���ݵ�ǰ�ڵ�ͱߵĳ��ȷ�Χ����һ���µĽڵ������,���½ڵ������������Ҫ��
// Details:a.(OldNode, NewNode)֮��ľ���������ıߵķ�Χ�ڣ�b.�µı�NewEdge��һ���߶Σ����뱣֤�ñ����Ѿ����ڵı߲����н��㣨����OldNode�������ߣ���c.NewNode�����겻�������еı��ϣ��������߶��ϣ�
// Parameter: Node & new_node �½ڵ�
// Parameter: Node cur_node ��ǰ�ڵ�
// Parameter: int EdgeMaxLen �������ֵ
// Parameter: int EdgeMinLen ������Сֵ
//************************************
bool CreatNewNodeX_Y(Node& new_node, Node cur_node, int EdgeMaxLen, int EdgeMinLen)
{

	//�жϲ���
	if (EdgeMaxLen <= EdgeMinLen) return false;
	int cur_nodeX = cur_node.GetX();
	int cur_nodeY = cur_node.GetY();
	//ȡ��������ɣ���Ϊ�����ܹ�����Ҫ��ĵ������ѡһ��
	//��ȡ��Χ�����е�����Ҫ��ĵ�
	vector<Node> nodes_for_add;//�洢����Ҫ���node
	//x��y�ķ�Χ����һ��������������ȥһ��С������
	int x_max = (int)(sqrt(EdgeMaxLen) + cur_nodeX);
	int x_min = (int)(-sqrt(EdgeMaxLen) + cur_nodeX);
	int y_max = (int)(sqrt(EdgeMaxLen) + cur_nodeY);
	int y_min = (int)(-sqrt(EdgeMaxLen) + cur_nodeY);
	for (int i = x_min; i <= x_max; i++)
		for (int j = y_min; j <= y_max; j++)
		{
			if (i< (int)(sqrt(EdgeMinLen) + cur_nodeX) && i>(int)(-sqrt(EdgeMinLen) + cur_nodeX))
				if (j< (int)(sqrt(EdgeMinLen) + cur_nodeY) && j>(int)(-sqrt(EdgeMinLen) + cur_nodeY))
					continue;
			Node Nownode(i, j, new_node.GetID());
			if (IsNodeKeepAwayFromNodeArray(Nownode, EdgeMinLen) && IsNodeInEdgeArray(Nownode) == false && IsEdgeIntersectedEdgeArray(cur_node, Nownode) == false)
				nodes_for_add.push_back(Nownode);

		}
	if (nodes_for_add.size() == 0) return false;//����Ҳ�������Ҫ��ıߣ��򷵻�false
	int choose_id;
	if (nodes_for_add.size() == 1)
		choose_id = 0;
	else
		choose_id = RandomCreatFunc(0, nodes_for_add.size() - 1);
	new_node = nodes_for_add.at(choose_id);
	return true;

}
//************************************
// Method:    IsNodeConnected
// FullName:  IsNodeConnected
// Access:    public 
// Returns:   bool
// Qualifier: �ж������ڵ��Ƿ�����
// Parameter: Node node1
// Parameter: Node node2
//************************************
bool IsNodeConnected(Node node1, Node node2)
{
	Edge edge;
	Node edge_node1, edge_node2;
	vector<Edge>::const_iterator iter = EdgeArray.begin();
	for (; iter != EdgeArray.end(); ++iter)
	{
		edge = (*iter);
		if (edge.GetNode1() == node1 && edge.GetNode2() == node2)
			return true;
		else if (edge.GetNode1() == node2 && edge.GetNode2() == node1)
			return true;
	}
	return false;
}
//************************************
// Method:    CreatPlaneUndirectedGraph
// FullName:  CreatPlaneUndirectedGraph
// Access:    public 
// Returns:   void
// Qualifier:����ƽ����ͨ����ͼ
// Parameter: int NodeCounts �ڵ�����
// Parameter: int EdgeCounts �ߵ�����
// Parameter: int EdgeMaxLen �ߵ����ֵ
// Parameter: int EdgeMinLen �ߵ���Сֵ
//************************************
void CreatPlaneUndirectedGraph(int NodeCounts, int EdgeCounts, int EdgeMaxLen, int EdgeMinLen)
{
	//��������Сƽ����ͨ����ͼ
		//����һ���������
	int* randomArray = new int[NodeCounts];
	RandomArray(randomArray, NodeCounts);
	srand(time(NULL));
	//˳��ı���������У���ӱ�
	for (int i = 0; i < NodeCounts; ++i)
	{
		int Node_id = randomArray[i];
		//����ǵ�һ��������������Ϊ(0,0)
		if (i == 0)
		{
			Node new_node(0, 0, Node_id);
			NodeArray.push_back(new_node);
		}
		//�������ȷ��������
		else
		{
			//���Ѿ�ȷ������ĵ��У������ѡһ��������Ϊ���ӽڵ�
			int val = rand() % i;
			int static_val = val;
			Node choose_node = NodeArray.at(val);
			//��������Ҫ����½ڵ�
			Node new_node(0, 0, Node_id);
			//��������ڵ�����ʧ���ˣ���һ�����ӽڵ�
			while (CreatNewNodeX_Y(new_node, choose_node, EdgeMaxLen, EdgeMinLen) == false)
			{
				val = (val + 1) % i;
				if (static_val == val)//����Ѿ�������Ŀǰ���еĽڵ��ˣ���ôֱ���˳�����
				{
					cout << "��������С����ʱ���Ѿ�û�������µĽڵ��ˣ�" << endl;
					exit(0);
				}

				choose_node = NodeArray.at(val);
			}
			//�����ڵ�����ɹ��ˣ����ߺͽڵ���ӽ�������
			Edge new_edge(choose_node, new_node);
			EdgeArray.push_back(new_edge);
			NodeArray.push_back(new_node);


		}
	}
	//�����ʣ��ı�
	while (EdgeArray.size() < EdgeCounts)
	{
		if (AddEdgeToGraph() == false) {
			cout << "�޷������ӱߣ�" << endl;
			break;
		}

	}
}
//************************************
// Method:    printInformationToCSV
// FullName:  printInformationToCSV
// Access:    public 
// Returns:   void
// Qualifier:���ڵ�ͱ������csv�ļ���
//************************************
void printInformationToCSV()
{
	Node node;
	Edge edge;
	Node edge_node1, edge_node2;
	FILE* fd = NULL;
	if ((fd = fopen("Node.csv", "wt+")) != NULL)
	{
		//�洢������Ϣ
		fprintf(fd, "%s,%s,%s\n", "Node_ID", "Node_X", "Node_Y");
		//�洢�ڵ���Ϣ
		vector<Node>::const_iterator ite = NodeArray.begin();
		for (; ite != NodeArray.end(); ++ite)
		{
			node = (*ite);
			fprintf(fd, "%d,%d,%d\n", node.GetID(), node.GetX(), node.GetY());
		}
		fprintf(fd, "\n");
	}
	fclose(fd);
	fd = NULL;
	if ((fd = fopen("Edge.csv", "wt+")) != NULL)
	{	//�洢������Ϣ
		fprintf(fd, "%s,%s,%s,%s\n", "Edge_node1_x", "Edge_node1_y", "Edge_node2_x", "Edge_node2_y");
		//�洢�ڵ���Ϣ
		vector<Edge>::const_iterator iter = EdgeArray.begin();
		for (; iter != EdgeArray.end(); ++iter)
		{
			edge = (*iter);
			edge_node1 = edge.GetNode1();
			edge_node2 = edge.GetNode2();
			fprintf(fd, "%d,%d,%d,%d\n", edge_node1.GetX(), edge_node1.GetY(), edge_node2.GetX(), edge_node2.GetY());
		}
		fprintf(fd, "\n");

	}
	fclose(fd);
	fd = NULL;

}
