
#ifndef _MYALGORITHM_H
#define _MYALGORITHM_H
#include <iostream>
#include "pch.h"
#include <vector>
#include "Node.h"
#include "Edge.h"
#include "time.h"
#include "math.h"
#include <random>
#include "stdio.h"
using namespace std;
int max(int x, int y);
int min(int x, int y);
double mult(Node a, Node b, Node c);
bool intersect(Node aa, Node bb, Node cc, Node dd);
double determinant(double v1, double v2, double v3, double v4);
bool IsIntersect(Edge edge1, Edge edge2);
const int on_segment(Node node, Node& node1, Node& node2);
bool  IsEdgeIntersectedEdgeArray(Edge& edge);
bool  IsEdgeIntersectedEdgeArray(Node cur_node, Node new_node);
bool IsNodeInEdgeArray(const Node& node);
int RandomCreatFunc(int interval_min, int interval_max);
void RandomArray(int* arr, int Amounts);
double Distance(Node a, Node b);
bool IsNodeKeepAwayFromNodeArray(Node node, int min_distance);
bool AddEdgeToGraph();
bool CreatNewNodeX_Y(Node& new_node, Node cur_node, int EdgeMaxLen, int EdgeMinLen);
bool IsNodeConnected(Node node1, Node node2);
void CreatPlaneUndirectedGraph(int NodeCounts, int EdgeCounts, int EdgeMaxLen, int EdgeMinLen);
void printInformationToCSV();
#endif
#pragma once
