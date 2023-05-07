#include<easyx.h>
#include<iostream>
#include<stdlib.h>
#include<map>
#include<conio.h>
#include"Point.h"
#include"Gragh.h"
#include<time.h>
#include<stdlib.h>

#define ROW 1000
#define COL 1000
//const int mod = 1e3;
map <pair<int, int>, bool> mp;
Gragh G;
using namespace std;

bool check(Line o, int Edgecnt);
void NewGragh(int NodeNum, int EdgeNum);

//初始化
void init()
{
	initgraph(ROW, COL);//打开图形界面
	//MoveWindow(NULL, 0, 0,COL,ROW,false);
	setbkcolor(WHITE);
	cleardevice();
}

//画地图
void drawMap()
{
	BeginBatchDraw();//批量画图
	//for (int i = 0; i < MAP_ROW; i++)
	//{
	//	for (int j = 0; j < MAP_COL; j++)
	//	{
	//		switch (map[i][j])//根据二维数组的值画地图
	//		{
	//		case 空:
	//			setfillcolor(WHITE);//空为白色
	//			fillrectangle(j * SIZE, i * SIZE, (j + 1) * SIZE, (i + 1) * SIZE);
	//			break;
	//		case 墙:
	//			setfillcolor(BLACK);//墙为黑色
	//			fillrectangle(j * SIZE, i * SIZE, (j + 1) * SIZE, (i + 1) * SIZE);
	//			break;
	//		case 蛇:
	//			setfillcolor(RED);//蛇为红色
	//			fillrectangle(j * SIZE, i * SIZE, (j + 1) * SIZE, (i + 1) * SIZE);
	//			break;
	//		case 食物:
	//			setfillcolor(BLUE);//食物为蓝色
	//			fillrectangle(j * SIZE, i * SIZE, (j + 1) * SIZE, (i + 1) * SIZE);
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}
	EndBatchDraw();//结束批量画图
}

int main()
{
	init();
	NewGragh(100, 200);
	//setaspectratio
	for (int i = 1; i <= 100; i++)
	{
		setfillcolor(BLACK);
		fillcircle(G.p[i].x, G.p[i].y,5);
	}
	for (int i= 1; i <=100; i++)
	{
		setlinecolor(BLUE);
		setlinestyle(PS_SOLID, 1);
		for (auto v : G.e[i]) {
			line(G.p[i].x, G.p[i].y, G.p[v].x, G.p[v].y);
		}
	}
	while (1)
	{
		//drawmap();
	}

	closegraph();//关闭图形窗口
	return 0;
}
void NewGragh(int NodeNum, int EdgeNum) {
	int Edgecnt = 0;
	G.p[1] = point(ROW / 2, COL / 2);
	for (int i = 2; i <= NodeNum; ++i) {
		//printf("-%d\n", i);
		int x = (1ll * rand() * rand()) % mod, y = (1ll * rand() * rand()) % mod;
		G.p[i] = point(x, y);
		if (i == 1) continue;
		bool flag = 0;
		for (int j = 1; j < i; ++j) {
			Line o = Line(G.p[i], G.p[j]);
			//生成新边
			//判断是否和原有边产生不合理交叉点
			if (check(o, Edgecnt)) {
				flag = 1;
				G.l[++Edgecnt] = o;
				G.add(i, j);
				mp[{i, j}] = 1;
				mp[{j, i}] = 1;
				break;
			}
		}
		if (flag == 0) {
			printf("重新生成第%d个点\n", i);
			i--;
		}
	}
	//建立联通图
	while (Edgecnt < EdgeNum) {
		printf("%d\n", Edgecnt);
		int x = rand() % NodeNum + 1, y = rand() % NodeNum + 1;//printf("%d %d %d\n", x,y,Edgecnt);
		if (mp[{x, y}] || mp[{y, x}])continue;
		mp[{x, y}] = mp[{y, x}] = 1;
		Line o = Line(G.p[x], G.p[y]);
		if (check(o, Edgecnt)) {
			G.l[++Edgecnt] = o;
			G.add(x, y);
			mp[{x, y}] = 1;
			mp[{y, x}] = 1;
		}
	}


}
bool check(Line o, int Edgecnt) {
	for (int k = 1; k <= Edgecnt; ++k) {
		if (judge(G.l[k], o)) {
			return 0;
		}
	}
	return 1;
}
