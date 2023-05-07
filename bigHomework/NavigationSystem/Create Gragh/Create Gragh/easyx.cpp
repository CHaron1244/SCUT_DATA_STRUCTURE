#include "easyx.h"
#include<easyx.h>
#include "Graph.h"
void init()
{
	initgraph(ROW, COL);//打开图形界面
	//MoveWindow(NULL, 0, 0,COL,ROW,false);
	setbkcolor(WHITE);
	cleardevice();
}