#include "easyx.h"
#include<easyx.h>
#include "Graph.h"
void init()
{
	initgraph(ROW, COL);//��ͼ�ν���
	//MoveWindow(NULL, 0, 0,COL,ROW,false);
	setbkcolor(WHITE);
	cleardevice();
}