#pragma once
#ifndef Graph_H
#define Graph_H
#define ll long long
#include "Point.h"
#include <vector>
#include <map>
#include <queue>
#define ROW 1000
#define COL 1000
using namespace std;
const int maxn = 1e4 + 100;
const int mod = 1e3;
class Edge {
public:
	int u, v;//两个顶点(编号)
	int capacity;//车容量
	int flow;//当前在这条路上的车数量
	int length;//Edge的长度
	Edge() {

	}
	Edge(int _u, int _v, point p1 = point(0, 0), point p2 = point(0, 0)) {
		u = _u, v = _v;
		length = dist(p1, p1);
		capacity = length / 50; //capacity应该与distance成正比
	}
};
class Graph {
public:
	int cnt = 0;
	bool vis[maxn];
	vector <Edge> e[maxn];
	point p[maxn];
	Line l[maxn * 100];//Line只是开了1e6
	int NodeNum, EdgeNum;
	vector <int> NearestPoint;
	priority_queue < pair<double, int>, vector < pair <double, int> >, greater<pair<double, int> > > q;
	vector <int> win_cnt[5];//存每一块区域内点的数量
	vector <int> behalf_point[5];//存每一块区域代表点的编号（也可以为空，可以先标记为-1）
	vector <bool> point_much[5];//表示某个区域是否需要使用选出来的代表点(因为我的操作会把这个区域内的代表点都选出来,但不一定都需要使用,比如点过少的情况下)
	vector <int> parent[5];//BUG:[]里面不能填NodeNum，TODO  表示这个点在哪个区域内(1-256)
	vector <Edge> E[5][maxn + 5000];
	vector <Edge> Shortestpath;
	vector <Edge> LeastTime;
	int fa[maxn];
	int tof[maxn];
	double dis[maxn];
	bool is[5000][5000];
	map <pair<int, int>, bool> mp;
	void draw(point lu, point rd, double big);
	int findpos(point p, int num);//找该点的第num个图的第几个区域
	Graph();
	void add(int u, int v);
	void NewGraph(int NodeNum, int EdgeNum);
	void NewGraph_2(int NodeNum, int EdgeNum);
	void NewGraph1_1(int NodeNum, int EdgeNum);
	bool check(Line o, int Edgecnt);
	bool IsConnected();
	void dfs(int u, int fa);
	void FindNearestPoint(point o, int num);
	void  Dij(int x, int y);
	void init(int num);
	double f(double x);
	double cross_time(Edge e);
	bool point_in_block(point p, point lu, point rd);
	void lessen(point lu, point rd, int num);
	void update_flow();
	void LeastCrossTime(int x, int y);
};
#endif // !Graph_H