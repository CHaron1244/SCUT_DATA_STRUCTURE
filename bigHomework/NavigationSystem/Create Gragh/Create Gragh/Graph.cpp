#include "Graph.h"
#include "Point.h"
#include <queue>
using namespace std;

Graph::Graph() {
	NodeNum = EdgeNum = 0;
}
void Graph::add(int u, int v) {
	e[u].push_back(Edge(u, v));
	e[v].push_back(Edge(v, u));
}
void Graph::NewGraph(int NodeNum, int EdgeNum) {
	int Edgecnt = 0;
	p[1] = point(ROW / 2, COL / 2);
	for (int i = 2; i <= NodeNum; ++i) {
		int x = (1ll * rand() * rand()) % mod, y = (1ll * rand() * rand()) % mod;
		p[i] = point(x, y);
		if (i == 1) continue;
		bool flag = 0;
		for (int j = 1; j < i; ++j) {
			Line o = Line(p[i], p[j]);
			//生成新边
			//判断是否和原有边产生不合理交叉点
			if (check(o, Edgecnt)) {
				flag = 1;
				l[++Edgecnt] = o;
				add(i, j);
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
		Line o = Line(p[x], p[y]);
		if (check(o, Edgecnt)) {
			l[++Edgecnt] = o;
			add(x, y);
			mp[{x, y}] = 1;
			mp[{y, x}] = 1;
		}
	}
}

void Graph::NewGraph_2(int NodeNum, int EdgeNum) {//思路：先生成100个点，再慢慢连边
	int Edgecnt = 0;//开始边数为0
	p[1] = point(ROW / 2, COL / 2); //左上角为(0,0)
	for (int i = 2; i <= NodeNum; ++i) { //这里先只生成NodeNum个点
		int x = (1ll * rand() * rand()) % mod, y = (1ll * rand() * rand()) % mod, j;
		p[i] = point(x, y);
		bool overlap = 0;//判断是否跟之前的点重复的标志
		for (j = 1; j < i; j++) {//判断是否跟之前的点重复(置flag==0)目前i是点的个数
			if (p[j].x == p[i].x && p[j].y == p[i].y) {//j与i重复
				overlap = 1;//标志位置
				break;
			}
		}
		if (overlap == 1) {//有重复点
			printf("重新生成第%d个点\n", i);
			i--;
		}
	}
	//至此所有点已经生成，所有边还未生成
	//可以生成2个随机序列，长度为可选取的中心点的个数，一个为点的编号(1-NodeNum)，一个为发散边的数量
	//之后在每个随机的中心点向外发散
	int temp = 1;//中心点个数
	int* random1 = new int[temp];//点的编号
	int* random2 = new int[temp];//发散边的数量
	for (int i = 0; i < temp; i++) {
		random1[i] = rand() % NodeNum;
		random2[i] = rand() % 10;//10是自己定的，需要改
	}
	//现在开始发散
	for (int i = 0; i < temp; i++) {//遍历每一个随机的中心点
		int pos = random1[i];//中心点编号
		for (int j = 0; j < random2[i]; j++) {//从p[pos]发散出random2[i]条边
			int temp_pos = rand() % NodeNum;//要改（需求是随机一个点编号）
			if (mp[{pos, temp_pos}] || mp[{temp_pos, pos}])//已经有边了
				continue;
			Line o = Line(p[pos], p[temp_pos]);
			if (check(o, Edgecnt)) {
				l[++Edgecnt] = o;
				add(pos, temp_pos);
				mp[{pos, temp_pos}] = 1;
				mp[{temp_pos, pos}] = 1;
			}
		}
		if (Edgecnt >= (int)(0.8 * EdgeNum))
			break;
	}
	//又有想法：若要模拟真正的城市连边，上述做法不够
	//因为仅仅有中心城市(eg:北上广)向外发散的边,但小城市之间应该也有部分边，只是数量较少
	//需要增加:中心点可以发散出总边数的80-90%，然后其余边就随机取两个顶点连边(这两个点最好都不是中心点)
	while (Edgecnt < EdgeNum) { //这里接下来就是随机取点连边
		int x = rand() % NodeNum + 1, y = rand() % NodeNum + 1;//产生的是点的序号
		if (mp[{x, y}] || mp[{y, x}])//已经有边了
			continue;
		Line o = Line(p[x], p[y]);
		if (check(o, Edgecnt)) {
			l[++Edgecnt] = o;
			add(x, y);
			mp[{x, y}] = 1;
			mp[{y, x}] = 1;
		}
	}
}
bool Graph::check(Line o, int Edgecnt) {
	for (int k = 1; k <= Edgecnt; ++k) {
		if (judge(l[k], o)) {
			return 0;
		}
	}
	return 1;
}


void Graph::NewGraph1_1(int NodeNum, int EdgeNum) {
	this->NodeNum = NodeNum;
	this->EdgeNum = EdgeNum;
	for (int i = 1; i <= NodeNum; ++i) {
		e[i].clear();
	}
	int Edgecnt = 0;//开始边数为0
	p[1] = point(ROW / 2, COL / 2); //左上角为(0,0)
	for (int i = 1; i <= NodeNum; ++i) mp[{i, i}] = 1;
	for (int i = 2; i <= NodeNum; ++i) {
		int x = (1ll * rand() * rand()) % mod, y = (1ll * rand() * rand()) % mod;
		p[i] = point(x, y);
		bool overlap = 1;
		bool flag = 0;
		for (int j = 1; j < i; ++j) {
			if (p[i].x == p[j].x && p[i].y == p[j].y) {
				overlap = 0;
				break;
			}
		}
		if (overlap) {
			int cnt = 0;
			int tmp = rand() % i;
			if (!tmp) tmp = 1;
			while (cnt < i) {
				Line o = Line(p[i], p[tmp]);
				if (dist(p[i], p[tmp]) < 2000 && check(o, Edgecnt)) {
					flag = 1;
					l[++Edgecnt] = o;
					add(i, tmp);
					mp[{i, tmp}] = 1;
					mp[{tmp, i}] = 1;
					break;
				}
				++tmp;
				++cnt;
				tmp %= i;
				if (tmp == 0) tmp = 1;
			}
		}
		if (!overlap || !flag) {
			printf("重新生成第%d个点\n", i);
			i--;
		}
	}

	int temp = 20;//中心点个数
	int* random1 = new int[temp];//点的编号
	int* random2 = new int[temp];//发散边的数量
	random1[0] = 1;
	random2[0] = 10;
	for (int i = 1; i < temp; i++) {
		random1[i] = (rand() % NodeNum) + 1;
		random2[i] = rand() % 10;//10是自己定的，需要改
	}
	//现在开始发散
	for (int i = 0; i < temp; i++) {//遍历每一个随机的中心点
		int pos = random1[i];//中心点编号
		for (int j = 0; j < random2[i]; j++) {//从p[pos]发散出random2[i]条边
			int temp_pos = (rand() % NodeNum) + 1;//要改（需求是随机一个点编号）
			if (mp[{pos, temp_pos}] || mp[{temp_pos, pos}])//已经有边了
				continue;
			if (dist(p[pos], p[temp_pos]) > 1000) continue;
			Line o = Line(p[pos], p[temp_pos]);
			if (check(o, Edgecnt)) {
				l[++Edgecnt] = o;
				add(pos, temp_pos);
				mp[{pos, temp_pos}] = 1;
				mp[{temp_pos, pos}] = 1;
			}
		}
		if (Edgecnt >= (int)(0.8 * EdgeNum))
			break;
	}
	//又有想法：若要模拟真正的城市连边，上述做法不够
	//因为仅仅有中心城市(eg:北上广)向外发散的边,但小城市之间应该也有部分边，只是数量较少
	//需要增加:中心点可以发散出总边数的80-90%，然后其余边就随机取两个顶点连边(这两个点最好都不是中心点)
	int cnt = 0;
	while (Edgecnt < EdgeNum) { //这里接下来就是随机取点连边
		++cnt;
		if (cnt >= NodeNum * sqrt(NodeNum)) {
			printf("要求边数过多，生成失败");
			while (1);
			system("pause");
		}
		//printf("%d\n", Edgecnt);
		int x = (rand() % NodeNum) + 1, y = (rand() % NodeNum) + 1;//产生的是点的序号
		if (mp[{x, y}] || mp[{y, x}])//已经有边了
			continue;
		Line o = Line(p[x], p[y]);
		if (check(o, Edgecnt)) {
			l[++Edgecnt] = o;
			add(x, y);
			mp[{x, y}] = 1;
			mp[{y, x}] = 1;
			cnt = 0;
		}
	}
	for (int i = 1; i <= NodeNum; ++i) {
		for (auto o : e[i]) {
			o.flow = o.length / 3;
			//默认参数3，可修改
		}
	}
	for (int i = 1; i <= 4; ++i) init(i);
}
void Graph::dfs(int u, int fa) {
	for (auto tmp : e[u]) {
		if (tmp.v == fa) continue;
		if (vis[tmp.v]) continue;
		vis[tmp.v] = 1;
		++cnt;
		dfs(tmp.v, u);
	}
}
bool Graph::IsConnected() {
	memset(vis, 0, sizeof(vis));
	cnt = 1;
	vis[1] = 1;
	dfs(1, 0);
	return cnt == NodeNum;

}
void Graph::FindNearestPoint(point o, int num) {
	while (!q.empty()) q.pop();
	NearestPoint.clear();
	while (num > NodeNum) {
		printf("num is over the bound.\n");
		printf("Please enter the num again:\n");
		scanf_s("%d", &num);
	}
	for (int i = 1; i <= NodeNum; ++i) {
		q.push({ dist(o,p[i]),i });
	}
	while (num && !q.empty()) {
		num--;
		NearestPoint.push_back(q.top().second);
		q.pop();
	}
}

void Graph::Dij(int x, int y) {
	Shortestpath.clear();
	while (!q.empty()) q.pop();
	for (int i = 1; i <= NodeNum; ++i) fa[i] = 0, vis[i] = 0, dis[i] = 1e18;
	fa[x] = x;
	dis[x] = 0;
	q.push({ 0,x });
	while (!q.empty()) {
		auto tmp = q.top();
		q.pop();
		if (vis[tmp.second]) {
			continue;
		}
		vis[tmp.second] = 1;
		if (tmp.second == y) {
			int cur = y;
			while (cur != x) {
				Shortestpath.push_back(Edge(cur, fa[cur]));
				cur = fa[cur];
			}
			break;
		}
		for (auto cur : e[tmp.second]) {
			if (vis[cur.v]) continue;
			if (dis[cur.v] > dis[tmp.second] + dist(p[tmp.second], p[cur.v])) {
				dis[cur.v] = dis[tmp.second] + dist(p[tmp.second], p[cur.v]);
				fa[cur.v] = tmp.second;
				q.push({ dis[cur.v],cur.v });
			}
		}
	}
}
void Graph::init(int num) { //传入初始化图的编号(1-4对应8-64)
	int win_row = pow(2, num) * 4, win_col = pow(2, num) * 4;//数量
	point_much[num].clear();
	win_cnt[num].clear();
	behalf_point[num].clear();
	parent[num].clear();

	for (int i = 1; i <= win_row * win_col + 10; ++i) {
		point_much[num].push_back(0);//point_much[][]:1-win_row*win_col(第二维)	取值:true,false
		win_cnt[num].push_back(0);//win_cnt[][]:1-win_row*win_col(第二维)	取值:0-NodeNum 
		behalf_point[num].push_back(-1);//behalf_point[][]:1-NodeNum(第二维)	取值:1-NodeNum
	}
	for (int i = 1; i <= NodeNum + 10; ++i) {
		parent[num].push_back(-1);//parent[][]:1-NodeNum(第二维)	取值:1-win_row*win_col
		E[num][i].clear();
	}
	lessen(point(0, 0), point(ROW, COL), num);
}
double Graph::f(double x) {//100需要修改(常数c)
	return x <= 100 ? 1 : 1 + pow(2.71828, x);
}
double Graph::cross_time(Edge e) {//通过e这条边的时间(100需要修改)
	return 100 * e.length * f((double)e.flow / e.capacity);
}
bool Graph::point_in_block(point p, point lu, point rd) {//左上，右下
	return (lu.x <= p.x&& p.x <= rd.x&& lu.y <= p.y&& p.y <= rd.y);
}
void Graph::lessen(point lu, point rd, int num) {//参数:给定一定窗口大小的窗口的左上点与右下点(num=1-4)
	int win_row = pow(2, num) * 4, win_col = pow(2, num) * 4;
	int win_num = win_row * win_col;
	int len_row = ROW / win_row, len_col = COL / win_col;//这个东西需要前端提供，表示每一块区域的长&宽
	for (int i = 1; i <= NodeNum; ++i) {
		int x = (p[i].x - 1) / len_row + 1, y = (p[i].y - 1) / len_col + 1;
		if (x >	64 || x < 1 || y < 1 || y>64) {//点不在有效区域内
			parent[num][i] = -1;
			continue;
		}
		//计算点所在区域
		int tmp = (x - 1) * win_col + y;
		if (tmp<1 || tmp>win_num) continue;
		point lu_temp = point(lu.x + (x - 1) * len_row, lu.y + (y - 1) * len_row);
		point rd_temp = point(rd.x - (win_row - x) * len_row, rd.y - (win_col - y) * len_col);//找出当前这个区域内的左上点与右下点
		if (point_in_block(p[i], lu_temp, rd_temp)) {
			parent[num][i] = tmp;//编号为i的点在区域编号为temp的区域内
			win_cnt[num][tmp]++;
			//还需要更新代表点
			if (dist(lu_temp, p[i]) < dist((lu_temp + rd_temp) * 0.5, p[behalf_point[num][tmp]])) //behalf可能一开始没有
				behalf_point[num][tmp] = i;//temp区域的代表点的编号为k					
		}
		else continue;
		point_much[num][tmp] = 1||(win_cnt[num][tmp] >= 0.02 * NodeNum / (double)(pow(2, num)));//点过多，为true则表示需要选behalf
	}
	//memset(is, 0, sizeof(is));
	//for (int i = 1; i <= NodeNum; ++i) {//重新建图
	//	for (auto u : e[i]) {
	//		int fu = parent[num][u.u], fv = parent[num][u.v];
	//		if (fu == -1 || fv == -1 || point_much[num][fu] == 0 || point_much[num][fv] == 0) continue;
	//		else
	//		{
	//			fu = u.u + win_num, fv = u.v + win_num;	
	//			E[num][fu].push_back(Edge(fu, fv));
	//			E[num][fv].push_back(Edge(fv, fu));
	//		}//给孤立点连边
	//		//给u和v所在区域连边
	//		if (is[fu][fv]) continue;
	//		is[fu][fv] = is[fv][fu] = 1;
	//		E[num][fu].push_back(Edge(fu, fv));
	//		E[num][fv].push_back(Edge(fv, fu));
	//	}
	//}
	//显示子图
	//for (int i = 1; i <= NodeNum; i++) {
	   // for (int j = i + 1; j <= NodeNum; j++) {
	   //	 if (mp[{i, j}] || mp[{j, i}]) {//如果有边才会考虑接下来的操作
	   //		 int behalf_i = behalf_point[num][parent[num][i]];//i所在区域的代表点的编号
	   //		 int behalf_j = behalf_point[num][parent[num][j]];//j所在区域的代表点的编号
	   //		 if (behalf_i == behalf_j&& !point_much[num][parent[num][i]]) {//两个点在同一个区域内并且这个区域内点不多(边才需要显示)
	   //			 //直接显示point[i]和point[j]这条边
	   //		 }
	   //		 if (behalf_i != behalf_j) {//在不同区域,再判断有没有哪个区域点多
	   //			 if (point_much[num][parent[num][i]] && point_much[num][parent[num][j]]) { //两个区域点都多(都用代表点连接)
	   //				 //显示point[behalf_i]和point[behalf_j]
	   //			 }
	   //			 else if (point_much[num][parent[num][i]] && !point_much[num][parent[num][j]]) {
	   //				 //显示point[behalf_i]和point[j]
	   //			 }
	   //			 else if (!point_much[num][parent[num][i]] && point_much[num][parent[num][j]]) {
	   //				 //显示point[i]和point[behalf_j]
	   //			 }
	   //			 else {//两个区域点都少(直接连接)
	   //				 //显示point[i]和point[j]
	   //			 }
	   //		 }
	   //	 }
	   // }
	//}

	//照着这个图打印，就行，要考虑是否要代表点的问题！！！

	//for (int i = 1; i <= 16; i++) {//行
	   // for (int j = 1; j <= 16; j++) {//列
	   //	 int temp = (i - 1) * 16 + j;//当前区域的编号（1-256）
	   //	 point lu_temp = point(lu.x + (i - 1) * len_row, lu.y + (j - 1) * len_row);
	   //	 point rd_temp = point(rd.x - (win_row - i) * len_row, rd.y - (win_col - j) * len_col);//找出当前这个区域内的左上点与右下点
	   //	 //接下来统计在这个区域内点的数量是否达到了(比如说)总点数(NodeNum)的2%
	   //	 for (int k = 1; k <= NodeNum; k++) { //遍历每一个顶点(编号从1开始)
	   //		 bool flag = 0;//用来至少填充一下behalf_point数组
	   //		 if (point_in_block(p[k], lu_temp, rd_temp)) {
	   //			 parent[k] = temp;//编号为k的点在区域编号为temp的区域内
	   //			win_cnt[temp]++;
	   //			//还需要更新代表点
	   //			if (dist(lu_temp, p[k]) < dist(lu_temp, p[behalf_point[temp]])) //behalf可能一开始没有
	   //				behalf_point[temp] = k;//temp区域的代表点的编号为k					
	   //		 }
	   //	 }
	   //	 if (win_cnt[temp] >= 0.02 * NodeNum) {//点过多，需要选behalf
	   //		 point_much[temp] = true;
	   //	 }
	   // }
	//}

	//现在开始重构图
	//目标:如果区域内的点之间有连边且point_much为true，则不显示
	//如果区域内的点与区域外的点有连边且point_much为true，则用代表点替换本区域内的这些点
	//for (int i = 1; i <= NodeNum; i++) {
	   // for (int j = i + 1; j <= NodeNum; j++) {
	   //	 if (mp[{i, j}] || mp[{j, i}]) {//如果有边才会考虑接下来的操作
	   //		 int behalf_i = behalf_point[parent[i]];//i所在区域的代表点的编号
	   //		 int behalf_j = behalf_point[parent[j]];//j所在区域的代表点的编号
	   //		 if (behalf_i == behalf_j&& !point_much[parent[i]]) {//两个点在同一个区域内并且这个区域内点不多(边才需要显示)
	   //			 //显示这条边
	   //			 //TODO
	   //		 }
	   //		 if (behalf_i != behalf_j) {//在不同区域
	   //			 //判断有没有哪个区域点多
	   //			 if (point_much[parent[i]] && point_much[parent[j]]) { //两个区域点都多(都用代表点连接)
	   //				 //显示point[behalf_i]和point[behalf_j]
	   //			 }
	   //			 else if (point_much[parent[i]] && !point_much[parent[j]]) {
	   //				 //显示point[behalf_i]和point[j]
	   //			 }
	   //			 else if (!point_much[parent[i]] && point_much[parent[j]]) {
	   //				 //显示point[i]和point[behalf_j]
	   //			 }
	   //			 else {//两个区域点都少(直接连接)
	   //				 //显示point[i]和point[j]
	   //			 }
	   //		 }
	   //	 }
	   // }
	//}
}
int Graph::findpos(point o, int num) {
	int win_row = pow(2, num) * 4, win_col = pow(2, num) * 4;
	int win_num = win_row * win_col;
	int len_row = ROW / win_row, len_col = COL / win_col;
	int x = (o.x - 1) / len_row + 1, y = (o.y - 1) / len_col + 1;
	return (x - 1) * win_col + y;
}
void Graph::draw(point lu, point rd, double big) {
	int num = big / 20 + 1;
	int win_row = pow(2, num) * 4, win_col = pow(2, num) * 4;
	int win_num = win_row * win_col;
	int len_row = ROW / win_row, len_col = COL / win_col;
	for (int i = 1; i <= NodeNum; ++i) {
		int x = (p[i].x - 1) / len_row + 1, y = (p[i].y - 1) / len_col + 1;
		if (x > 16 || x < 1 || y < 1 || y>16) {//点不在有效区域内
			continue;
		}
		int tmp = (x - 1) * win_col + y;
		int u = i;
		if (point_much[num][tmp]) {
			u = behalf_point[num][tmp];
			for (auto o : e[u]) {
				int pos = findpos(p[o.v], num);
				if (pos<1 || pos>win_num) continue;
				int v = o.v;
				if (point_much[num][pos]) {
					v = behalf_point[num][pos];
				}
				//line(p[u].x,p[u].y,p[v].x,p[v].y);
				//画点v和u之间的线，p[v],p[u];!!!
			}
		}
	}
}
void Graph::update_flow() {//更新车流量
	for (int i = 1; i <= NodeNum; ++i) {
		for (auto &o : e[i]) {
			/*if (o.flow <= o.length / 3) {
				o.flow += o.length * 0.1;
				o.flow *= 1 + (rand() % 100) / 100.0;
				continue;
			}
			else if (o.flow >= o.length * 3) {
				o.flow -= o.length * 0.1;
				o.flow *= 1 - (rand() % 100) / 100.0;
				continue;
			}
			if (rand() & 1) {
				o.flow *= 1 + (rand() % 100) / 100.0;
			}
			else {
				o.flow *= 1 - (rand() % 100) / 100.0;
			}*/
			o.flow = rand() % 10 + 1;
		}
	}

}
void Graph::LeastCrossTime(int x, int y) {
	while (!q.empty()) q.pop();
	for (int i = 1; i <= NodeNum; ++i) fa[i] = 0, vis[i] = 0, dis[i] = 1e18, tof[i] = 0;
	fa[x] = x;
	tof[x] = 0;
	dis[x] = 0;
	q.push({ 0,x });
	while (!q.empty()) {
		auto tmp = q.top();
		q.pop();
		if (vis[tmp.second]) {
			continue;
		}
		vis[tmp.second] = 1;
		if (tmp.second == y) {
			int cur = y;
			while (cur != x) {
				LeastTime.push_back(Edge(cur, fa[cur]));
				//要改
				LeastTime[LeastTime.size() - 1].flow = tof[cur];
				cur = fa[cur];
			}
			break;
		}
		for (auto cur : e[tmp.second]) {
			if (vis[cur.v]) continue;
			if (dis[cur.v] > dis[tmp.second] + cross_time(cur)) {
				dis[cur.v] = dis[tmp.second] + cross_time(cur);
				fa[cur.v] = tmp.second;
				q.push({ dis[cur.v],cur.v });
				tof[cur.v] = cross_time(cur);
			}
		}
	}
}