#include<easyx.h>
#include<iostream>
#include<stdlib.h>
#include<map>
#include<conio.h>
#include"Point.h"
#include"Graph.h"
#include "easyx.h"
#include<time.h>
#include<stdlib.h>

using namespace std;
Graph G;
//初始化
int main()
{
	srand(time(0));
    G.NewGraph1_1(100, 200);
	if (G.IsConnected()) 
		printf("Connected\n");
	else 
		printf("Unconnected\n");
	setaspectratio;
	init();
	for (int i = 1; i <= G.NodeNum; i++)
	{
		setfillcolor(BLACK);
		fillcircle(G.p[i].x, G.p[i].y, 10);
	}
	for (int i = 1; i <= G.NodeNum; i++)
	{
		setlinecolor(BLUE);
		setlinestyle(PS_SOLID, 5);
		for (auto tmp : G.e[i]) {
			line(G.p[tmp.u].x, G.p[tmp.u].y, G.p[tmp.v].x, G.p[tmp.v].y);
		}
	}
	Sleep(5e3);
	closegraph();
	//
	//double x, y;
	//int num;
	//printf("Please enter x,y,num:\n");
	//scanf_s("%lf%lf%d", &x, &y, &num);
	//vector <int>tmp = 
	//G.FindNearestPoint(point(x,y),num);
	//bool vis[1001];
	//init();
	//for (int i = 1; i <= G.NodeNum; ++i) {
	//	vis[i] = 0;
	//}
	//for (auto v:tmp)
	//{
	//	vis[v] = 1;
	//	setfillcolor(RED);
	//	fillcircle(G.p[v].x, G.p[v].y, 5);
	//}
	//for (auto x : tmp) {
	//	setlinecolor(GREEN);
	//	setlinestyle(PS_SOLID, 5);
	//	for (auto  y: G.e[x]) {
	//		if (vis[y.v]) {
	//			line(G.p[y.u].x, G.p[y.u].y, G.p[y.v].x, G.p[y.v].y);
	//		}
	//	}
	//}
	//Sleep(5e3);
	//closegraph();

	//printf("Please enter the point id x,y:");
	//int pid1, pid2;
	//scanf_s("%d%d", &pid1,&pid2);
	//auto temp=G.Dij(pid1,pid2);
	//printf("%d\n", temp.size());
	//init();
	//for (auto E : temp) {
	//	setfillcolor(RED);
	//	fillcircle(G.p[E.u].x, G.p[E.u].y, 5);
	//	fillcircle(G.p[E.v].x, G.p[E.v].y, 5);
	//	setlinecolor(BLUE);
	//	setlinestyle(PS_SOLID, 5);
	//	line(G.p[E.u].x, G.p[E.u].y, G.p[E.v].x, G.p[E.v].y);

	//}
	//Sleep(1e5);

	//while (1)
	//{
	//	//drawmap();
	//}

	//closegraph();//关闭图形窗口
	
	return 0;
}
