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
// Qualifier:aa,和bb为一条线段两端点，cc和dd为另一条线段的两端点 相交返回true, 不相交返回false
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
//二阶矩阵的x乘运算
double determinant(double v1, double v2, double v3, double v4)  // 行列式
{
	return (v1 * v3 - v2 * v4);
}
//判断两个边(线段)是否相交 是-返回true 否-返回false
bool IsIntersect(Edge edge1, Edge edge2)
{
	Node a, b, c, d;
	a = edge1.GetNode1();
	b = edge1.GetNode2();
	c = edge2.GetNode1();
	d = edge2.GetNode2();
	return intersect(a, b, c, d);

}


//判断节点node,是否在node1和node2的线段上 是-返回1 否-返回0
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
//判断新边是否与现有的边相交（除去相邻的边）是-返回true 否-返回false
bool  IsEdgeIntersectedEdgeArray(Edge& edge)
{
	Node node1, node2;//边取出的两个节点
	Edge Aedge;//容器中取出的边
	Node edge_node1, edge_node2;
	edge_node1 = edge.GetNode1();
	edge_node2 = edge.GetNode2();
	vector<Edge>::const_iterator iterator = EdgeArray.begin();
	for (; iterator != EdgeArray.end(); ++iterator)
	{
		Aedge = (*iterator);
		node1 = Aedge.GetNode1();
		node2 = Aedge.GetNode2();
		//如果两个边有同样的节点，则直接跳过
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
// Qualifier:根据当前节点和新节点的坐标，判断两者构成的新边是否会与现有的边相交
// Parameter: Node cur_node 当前节点
// Parameter: Node new_node 新节点
//************************************
bool  IsEdgeIntersectedEdgeArray(Node cur_node, Node new_node)
{
	Edge edge(cur_node, new_node);
	Edge Aedge;//容器中取出的边
	 //如果尚未有边，则返回false
	if (EdgeArray.size() == 0)
		return false;
	vector<Edge>::const_iterator iterator = EdgeArray.begin();
	for (; iterator != EdgeArray.end(); ++iterator)
	{
		Aedge = (*iterator);
		//如果旧节点是边的其中一个节点，则不需要判断，直接下一个循环
		if (Aedge.GetNode1() == cur_node || Aedge.GetNode2() == cur_node)
			continue;
		if (IsIntersect(edge, Aedge) == true)
			return true;
	}
	return false;
}
//判断节点是否在已存边的任意一条边上 是-返回true 否-返回false
bool IsNodeInEdgeArray(const Node& node)
{
	Node node1, node2;//边取出的两个节点
	Edge edge;//容器中取出的边
	int Counts = 0;
	//如果尚未有边，则返回false
	if (EdgeArray.size() == 0)
		return false;
	//将节点与所有边进行判断是否在线段上
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
// Qualifier: 根据区间生成随机数
// Parameter: int interval_min 区间左值
// Parameter: int interval_max 区间右值
//************************************
int RandomCreatFunc(int interval_min, int interval_max)
{
	if (interval_min >= interval_max)
		return INT_MAX;
	//种子值是通过 random_device 类型的函数对象 rd 获得的。
	//每一个 rd() 调用都会返回不同的值，而且如果我们实现的 random_devic 是非确定性的，程序每次执行连续调用 rd() 都会产生不同的序列。
	random_device rd;
	default_random_engine e{ rd() };
	int random_num = 0;
	//分情况产生随机数，考虑3种情况：min<0&&max>0 、max<0和min>0
	if (interval_min >= 0)//min>0的情况
	{
		uniform_int_distribution<unsigned> a(interval_min, interval_max);
		random_num = a(e);
	}
	else if (interval_max > 0)//min<0&&max>0 的情况
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
	else//max<0的情况
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
// Qualifier:生成随机序列 输入的数组将被改变为随机序列
// Parameter: int * arr 输入的数组
// Parameter: int Amounts 数组大小
//************************************
void RandomArray(int* arr, int Amounts)
{
	for (int i = 0; i < Amounts; i++)
		arr[i] = 0;
	int count = 0;		//计数，
	while (count < Amounts)
	{
		int val = RandomCreatFunc(0, Amounts - 1);//随机确定下标
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
// Qualifier:求两个节点之间的距离
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
// Qualifier:判断节点是否远离现有的节点
// Parameter: Node node 节点
// Parameter: int min_distance 距离的最小值
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

	if (edge_for_add.size() == 0) return false;//如果找不到符合要求的边，则返回false
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
// Qualifier:根据当前节点和边的长度范围生成一个新的节点的坐标,且新节点的坐标必须符合要求；
// Details:a.(OldNode, NewNode)之间的距离在输入的边的范围内；b.新的边NewEdge是一条线段，必须保证该边与已经存在的边不能有交点（除了OldNode的其它边）；c.NewNode的坐标不能在已有的边上（即点在线段上）
// Parameter: Node & new_node 新节点
// Parameter: Node cur_node 当前节点
// Parameter: int EdgeMaxLen 长度最大值
// Parameter: int EdgeMinLen 长度最小值
//************************************
bool CreatNewNodeX_Y(Node& new_node, Node cur_node, int EdgeMaxLen, int EdgeMinLen)
{

	//判断参数
	if (EdgeMaxLen <= EdgeMinLen) return false;
	int cur_nodeX = cur_node.GetX();
	int cur_nodeY = cur_node.GetY();
	//取消随机生成，改为从已能够满足要求的点中随机选一个
	//获取范围内所有的满足要求的点
	vector<Node> nodes_for_add;//存储符合要求的node
	//x，y的范围是在一个大正方形中挖去一个小正方形
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
	if (nodes_for_add.size() == 0) return false;//如果找不到符合要求的边，则返回false
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
// Qualifier: 判断两个节点是否连接
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
// Qualifier:生成平面连通无向图
// Parameter: int NodeCounts 节点数量
// Parameter: int EdgeCounts 边的数量
// Parameter: int EdgeMaxLen 边的最大值
// Parameter: int EdgeMinLen 边的最小值
//************************************
void CreatPlaneUndirectedGraph(int NodeCounts, int EdgeCounts, int EdgeMaxLen, int EdgeMinLen)
{
	//先生成最小平面连通无向图
		//生成一个随机序列
	int* randomArray = new int[NodeCounts];
	RandomArray(randomArray, NodeCounts);
	srand(time(NULL));
	//顺序的遍历随机序列，添加边
	for (int i = 0; i < NodeCounts; ++i)
	{
		int Node_id = randomArray[i];
		//如果是第一个，设置其坐标为(0,0)
		if (i == 0)
		{
			Node new_node(0, 0, Node_id);
			NodeArray.push_back(new_node);
		}
		//否则，随机确定其坐标
		else
		{
			//从已经确定坐标的点中，随机挑选一个出来作为连接节点
			int val = rand() % i;
			int static_val = val;
			Node choose_node = NodeArray.at(val);
			//产生符合要求的新节点
			Node new_node(0, 0, Node_id);
			//如果产生节点坐标失败了，则换一个连接节点
			while (CreatNewNodeX_Y(new_node, choose_node, EdgeMaxLen, EdgeMinLen) == false)
			{
				val = (val + 1) % i;
				if (static_val == val)//如果已经遍历过目前所有的节点了，那么直接退出程序
				{
					cout << "在生成最小子树时，已经没法增加新的节点了！" << endl;
					exit(0);
				}

				choose_node = NodeArray.at(val);
			}
			//产生节点坐标成功了，将边和节点添加进容器中
			Edge new_edge(choose_node, new_node);
			EdgeArray.push_back(new_edge);
			NodeArray.push_back(new_node);


		}
	}
	//再添加剩余的边
	while (EdgeArray.size() < EdgeCounts)
	{
		if (AddEdgeToGraph() == false) {
			cout << "无法在增加边！" << endl;
			break;
		}

	}
}
//************************************
// Method:    printInformationToCSV
// FullName:  printInformationToCSV
// Access:    public 
// Returns:   void
// Qualifier:将节点和边输出到csv文件中
//************************************
void printInformationToCSV()
{
	Node node;
	Edge edge;
	Node edge_node1, edge_node2;
	FILE* fd = NULL;
	if ((fd = fopen("Node.csv", "wt+")) != NULL)
	{
		//存储基本信息
		fprintf(fd, "%s,%s,%s\n", "Node_ID", "Node_X", "Node_Y");
		//存储节点信息
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
	{	//存储基本信息
		fprintf(fd, "%s,%s,%s,%s\n", "Edge_node1_x", "Edge_node1_y", "Edge_node2_x", "Edge_node2_y");
		//存储节点信息
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
