﻿// CreatPlaneUndirectedGraph.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include "Node.h"
#include "Edge.h"
#include "MYAlgorithm.h"
#include <vector>
#include <iostream>
#include <thread>
#include <ctime> 
#include <iomanip>
using namespace std;
vector<Node> NodeArray;
vector<Edge> EdgeArray;
int main()
{
	//int node_counts, edge_counts;
	/*cin >> node_counts;
	cin >> edge_counts;*/
	CreatPlaneUndirectedGraph(300, 400, 100, 16);
	Node node;
	Edge edge;
	Node edge_node1, edge_node2;
	cout << "各个节点坐标为：" << endl;
	vector<Node>::const_iterator ite = NodeArray.begin();
	for (; ite != NodeArray.end(); ++ite)
	{
		node = (*ite);
		cout << node.GetID() << "  " << node.GetX() << "  " << node.GetY() << endl;
	}
	cout << "各个边为：" << endl;
	vector<Edge>::const_iterator iter = EdgeArray.begin();
	for (; iter != EdgeArray.end(); ++iter)
	{
		edge = (*iter);
		edge_node1 = edge.GetNode1();
		edge_node2 = edge.GetNode2();
		cout << edge_node1.GetID() << "  " << edge_node2.GetID() << endl;
	}
	printInformationToCSV();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
