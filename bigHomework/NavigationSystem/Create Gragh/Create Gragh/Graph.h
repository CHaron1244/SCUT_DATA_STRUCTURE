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
	int u, v;//��������(���)
	int capacity;//������
	int flow;//��ǰ������·�ϵĳ�����
	int length;//Edge�ĳ���
	Edge() {

	}
	Edge(int _u, int _v, point p1 = point(0, 0), point p2 = point(0, 0)) {
		u = _u, v = _v;
		length = dist(p1, p1);
		capacity = length / 50; //capacityӦ����distance������
	}
};
class Graph {
public:
	int cnt = 0;
	bool vis[maxn];
	vector <Edge> e[maxn];
	point p[maxn];
	Line l[maxn * 100];//Lineֻ�ǿ���1e6
	int NodeNum, EdgeNum;
	vector <int> NearestPoint;
	priority_queue < pair<double, int>, vector < pair <double, int> >, greater<pair<double, int> > > q;
	vector <int> win_cnt[5];//��ÿһ�������ڵ������
	vector <int> behalf_point[5];//��ÿһ����������ı�ţ�Ҳ����Ϊ�գ������ȱ��Ϊ-1��
	vector <bool> point_much[5];//��ʾĳ�������Ƿ���Ҫʹ��ѡ�����Ĵ����(��Ϊ�ҵĲ��������������ڵĴ���㶼ѡ����,����һ������Ҫʹ��,�������ٵ������)
	vector <int> parent[5];//BUG:[]���治����NodeNum��TODO  ��ʾ��������ĸ�������(1-256)
	vector <Edge> E[5][maxn + 5000];
	vector <Edge> Shortestpath;
	vector <Edge> LeastTime;
	int fa[maxn];
	int tof[maxn];
	double dis[maxn];
	bool is[5000][5000];
	map <pair<int, int>, bool> mp;
	void draw(point lu, point rd, double big);
	int findpos(point p, int num);//�Ҹõ�ĵ�num��ͼ�ĵڼ�������
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