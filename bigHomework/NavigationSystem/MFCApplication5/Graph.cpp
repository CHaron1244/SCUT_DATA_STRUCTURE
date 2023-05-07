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
			//�����±�
			//�ж��Ƿ��ԭ�б߲������������
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
			printf("�������ɵ�%d����\n", i);
			i--;
		}
	}
	//������ͨͼ
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

void Graph::NewGraph_2(int NodeNum, int EdgeNum) {//˼·��������100���㣬����������
	int Edgecnt = 0;//��ʼ����Ϊ0
	p[1] = point(ROW / 2, COL / 2); //���Ͻ�Ϊ(0,0)
	for (int i = 2; i <= NodeNum; ++i) { //������ֻ����NodeNum����
		int x = (1ll * rand() * rand()) % mod, y = (1ll * rand() * rand()) % mod, j;
		p[i] = point(x, y);
		bool overlap = 0;//�ж��Ƿ��֮ǰ�ĵ��ظ��ı�־
		for (j = 1; j < i; j++) {//�ж��Ƿ��֮ǰ�ĵ��ظ�(��flag==0)Ŀǰi�ǵ�ĸ���
			if (p[j].x == p[i].x && p[j].y == p[i].y) {//j��i�ظ�
				overlap = 1;//��־λ��
				break;
			}
		}
		if (overlap == 1) {//���ظ���
			printf("�������ɵ�%d����\n", i);
			i--;
		}
	}
	//�������е��Ѿ����ɣ����б߻�δ����
	//��������2��������У�����Ϊ��ѡȡ�����ĵ�ĸ�����һ��Ϊ��ı��(1-NodeNum)��һ��Ϊ��ɢ�ߵ�����
	//֮����ÿ����������ĵ����ⷢɢ
	int temp = 1;//���ĵ����
	int* random1 = new int[temp];//��ı��
	int* random2 = new int[temp];//��ɢ�ߵ�����
	for (int i = 0; i < temp; i++) {
		random1[i] = rand() % NodeNum;
		random2[i] = rand() % 10;//10���Լ����ģ���Ҫ��
	}
	//���ڿ�ʼ��ɢ
	for (int i = 0; i < temp; i++) {//����ÿһ����������ĵ�
		int pos = random1[i];//���ĵ���
		for (int j = 0; j < random2[i]; j++) {//��p[pos]��ɢ��random2[i]����
			int temp_pos = rand() % NodeNum;//Ҫ�ģ����������һ�����ţ�
			if (mp[{pos, temp_pos}] || mp[{temp_pos, pos}])//�Ѿ��б���
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
	//�����뷨����Ҫģ�������ĳ������ߣ�������������
	//��Ϊ���������ĳ���(eg:���Ϲ�)���ⷢɢ�ı�,��С����֮��Ӧ��Ҳ�в��ֱߣ�ֻ����������
	//��Ҫ����:���ĵ���Է�ɢ���ܱ�����80-90%��Ȼ������߾����ȡ������������(����������ö��������ĵ�)
	while (Edgecnt < EdgeNum) { //����������������ȡ������
		int x = rand() % NodeNum + 1, y = rand() % NodeNum + 1;//�������ǵ�����
		if (mp[{x, y}] || mp[{y, x}])//�Ѿ��б���
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
	int Edgecnt = 0;//��ʼ����Ϊ0
	p[1] = point(ROW / 2, COL / 2); //���Ͻ�Ϊ(0,0)
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
			printf("�������ɵ�%d����\n", i);
			i--;
		}
	}

	int temp = 20;//���ĵ����
	int* random1 = new int[temp];//��ı��
	int* random2 = new int[temp];//��ɢ�ߵ�����
	random1[0] = 1;
	random2[0] = 10;
	for (int i = 1; i < temp; i++) {
		random1[i] = (rand() % NodeNum) + 1;
		random2[i] = rand() % 10;//10���Լ����ģ���Ҫ��
	}
	//���ڿ�ʼ��ɢ
	for (int i = 0; i < temp; i++) {//����ÿһ����������ĵ�
		int pos = random1[i];//���ĵ���
		for (int j = 0; j < random2[i]; j++) {//��p[pos]��ɢ��random2[i]����
			int temp_pos = (rand() % NodeNum) + 1;//Ҫ�ģ����������һ�����ţ�
			if (mp[{pos, temp_pos}] || mp[{temp_pos, pos}])//�Ѿ��б���
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
	//�����뷨����Ҫģ�������ĳ������ߣ�������������
	//��Ϊ���������ĳ���(eg:���Ϲ�)���ⷢɢ�ı�,��С����֮��Ӧ��Ҳ�в��ֱߣ�ֻ����������
	//��Ҫ����:���ĵ���Է�ɢ���ܱ�����80-90%��Ȼ������߾����ȡ������������(����������ö��������ĵ�)
	int cnt = 0;
	while (Edgecnt < EdgeNum) { //����������������ȡ������
		++cnt;
		if (cnt >= NodeNum * sqrt(NodeNum)) {
			printf("Ҫ��������࣬����ʧ��");
			while (1);
			system("pause");
		}
		//printf("%d\n", Edgecnt);
		int x = (rand() % NodeNum) + 1, y = (rand() % NodeNum) + 1;//�������ǵ�����
		if (mp[{x, y}] || mp[{y, x}])//�Ѿ��б���
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
			//Ĭ�ϲ���3�����޸�
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
void Graph::init(int num) { //�����ʼ��ͼ�ı��(1-4��Ӧ8-64)
	int win_row = pow(2, num) * 4, win_col = pow(2, num) * 4;//����
	point_much[num].clear();
	win_cnt[num].clear();
	behalf_point[num].clear();
	parent[num].clear();

	for (int i = 1; i <= win_row * win_col + 10; ++i) {
		point_much[num].push_back(0);//point_much[][]:1-win_row*win_col(�ڶ�ά)	ȡֵ:true,false
		win_cnt[num].push_back(0);//win_cnt[][]:1-win_row*win_col(�ڶ�ά)	ȡֵ:0-NodeNum 
		behalf_point[num].push_back(-1);//behalf_point[][]:1-NodeNum(�ڶ�ά)	ȡֵ:1-NodeNum
	}
	for (int i = 1; i <= NodeNum + 10; ++i) {
		parent[num].push_back(-1);//parent[][]:1-NodeNum(�ڶ�ά)	ȡֵ:1-win_row*win_col
		E[num][i].clear();
	}
	lessen(point(0, 0), point(ROW, COL), num);
}
double Graph::f(double x) {//100��Ҫ�޸�(����c)
	return x <= 100 ? 1 : 1 + pow(2.71828, x);
}
double Graph::cross_time(Edge e) {//ͨ��e�����ߵ�ʱ��(100��Ҫ�޸�)
	return 100 * e.length * f((double)e.flow / e.capacity);
}
bool Graph::point_in_block(point p, point lu, point rd) {//���ϣ�����
	return (lu.x <= p.x&& p.x <= rd.x&& lu.y <= p.y&& p.y <= rd.y);
}
void Graph::lessen(point lu, point rd, int num) {//����:����һ�����ڴ�С�Ĵ��ڵ����ϵ������µ�(num=1-4)
	int win_row = pow(2, num) * 4, win_col = pow(2, num) * 4;
	int win_num = win_row * win_col;
	int len_row = ROW / win_row, len_col = COL / win_col;//���������Ҫǰ���ṩ����ʾÿһ������ĳ�&��
	for (int i = 1; i <= NodeNum; ++i) {
		int x = (p[i].x - 1) / len_row + 1, y = (p[i].y - 1) / len_col + 1;
		if (x >	64 || x < 1 || y < 1 || y>64) {//�㲻����Ч������
			parent[num][i] = -1;
			continue;
		}
		//�������������
		int tmp = (x - 1) * win_col + y;
		if (tmp<1 || tmp>win_num) continue;
		point lu_temp = point(lu.x + (x - 1) * len_row, lu.y + (y - 1) * len_row);
		point rd_temp = point(rd.x - (win_row - x) * len_row, rd.y - (win_col - y) * len_col);//�ҳ���ǰ��������ڵ����ϵ������µ�
		if (point_in_block(p[i], lu_temp, rd_temp)) {
			parent[num][i] = tmp;//���Ϊi�ĵ���������Ϊtemp��������
			win_cnt[num][tmp]++;
			//����Ҫ���´����
			if (dist(lu_temp, p[i]) < dist((lu_temp + rd_temp) * 0.5, p[behalf_point[num][tmp]])) //behalf����һ��ʼû��
				behalf_point[num][tmp] = i;//temp����Ĵ����ı��Ϊk					
		}
		else continue;
		point_much[num][tmp] = 1||(win_cnt[num][tmp] >= 0.02 * NodeNum / (double)(pow(2, num)));//����࣬Ϊtrue���ʾ��Ҫѡbehalf
	}
	//memset(is, 0, sizeof(is));
	//for (int i = 1; i <= NodeNum; ++i) {//���½�ͼ
	//	for (auto u : e[i]) {
	//		int fu = parent[num][u.u], fv = parent[num][u.v];
	//		if (fu == -1 || fv == -1 || point_much[num][fu] == 0 || point_much[num][fv] == 0) continue;
	//		else
	//		{
	//			fu = u.u + win_num, fv = u.v + win_num;	
	//			E[num][fu].push_back(Edge(fu, fv));
	//			E[num][fv].push_back(Edge(fv, fu));
	//		}//������������
	//		//��u��v������������
	//		if (is[fu][fv]) continue;
	//		is[fu][fv] = is[fv][fu] = 1;
	//		E[num][fu].push_back(Edge(fu, fv));
	//		E[num][fv].push_back(Edge(fv, fu));
	//	}
	//}
	//��ʾ��ͼ
	//for (int i = 1; i <= NodeNum; i++) {
	   // for (int j = i + 1; j <= NodeNum; j++) {
	   //	 if (mp[{i, j}] || mp[{j, i}]) {//����б߲Żῼ�ǽ������Ĳ���
	   //		 int behalf_i = behalf_point[num][parent[num][i]];//i��������Ĵ����ı��
	   //		 int behalf_j = behalf_point[num][parent[num][j]];//j��������Ĵ����ı��
	   //		 if (behalf_i == behalf_j&& !point_much[num][parent[num][i]]) {//��������ͬһ�������ڲ�����������ڵ㲻��(�߲���Ҫ��ʾ)
	   //			 //ֱ����ʾpoint[i]��point[j]������
	   //		 }
	   //		 if (behalf_i != behalf_j) {//�ڲ�ͬ����,���ж���û���ĸ�������
	   //			 if (point_much[num][parent[num][i]] && point_much[num][parent[num][j]]) { //��������㶼��(���ô��������)
	   //				 //��ʾpoint[behalf_i]��point[behalf_j]
	   //			 }
	   //			 else if (point_much[num][parent[num][i]] && !point_much[num][parent[num][j]]) {
	   //				 //��ʾpoint[behalf_i]��point[j]
	   //			 }
	   //			 else if (!point_much[num][parent[num][i]] && point_much[num][parent[num][j]]) {
	   //				 //��ʾpoint[i]��point[behalf_j]
	   //			 }
	   //			 else {//��������㶼��(ֱ������)
	   //				 //��ʾpoint[i]��point[j]
	   //			 }
	   //		 }
	   //	 }
	   // }
	//}

	//�������ͼ��ӡ�����У�Ҫ�����Ƿ�Ҫ���������⣡����

	//for (int i = 1; i <= 16; i++) {//��
	   // for (int j = 1; j <= 16; j++) {//��
	   //	 int temp = (i - 1) * 16 + j;//��ǰ����ı�ţ�1-256��
	   //	 point lu_temp = point(lu.x + (i - 1) * len_row, lu.y + (j - 1) * len_row);
	   //	 point rd_temp = point(rd.x - (win_row - i) * len_row, rd.y - (win_col - j) * len_col);//�ҳ���ǰ��������ڵ����ϵ������µ�
	   //	 //������ͳ������������ڵ�������Ƿ�ﵽ��(����˵)�ܵ���(NodeNum)��2%
	   //	 for (int k = 1; k <= NodeNum; k++) { //����ÿһ������(��Ŵ�1��ʼ)
	   //		 bool flag = 0;//�����������һ��behalf_point����
	   //		 if (point_in_block(p[k], lu_temp, rd_temp)) {
	   //			 parent[k] = temp;//���Ϊk�ĵ���������Ϊtemp��������
	   //			win_cnt[temp]++;
	   //			//����Ҫ���´����
	   //			if (dist(lu_temp, p[k]) < dist(lu_temp, p[behalf_point[temp]])) //behalf����һ��ʼû��
	   //				behalf_point[temp] = k;//temp����Ĵ����ı��Ϊk					
	   //		 }
	   //	 }
	   //	 if (win_cnt[temp] >= 0.02 * NodeNum) {//����࣬��Ҫѡbehalf
	   //		 point_much[temp] = true;
	   //	 }
	   // }
	//}

	//���ڿ�ʼ�ع�ͼ
	//Ŀ��:��������ڵĵ�֮����������point_muchΪtrue������ʾ
	//��������ڵĵ���������ĵ���������point_muchΪtrue�����ô�����滻�������ڵ���Щ��
	//for (int i = 1; i <= NodeNum; i++) {
	   // for (int j = i + 1; j <= NodeNum; j++) {
	   //	 if (mp[{i, j}] || mp[{j, i}]) {//����б߲Żῼ�ǽ������Ĳ���
	   //		 int behalf_i = behalf_point[parent[i]];//i��������Ĵ����ı��
	   //		 int behalf_j = behalf_point[parent[j]];//j��������Ĵ����ı��
	   //		 if (behalf_i == behalf_j&& !point_much[parent[i]]) {//��������ͬһ�������ڲ�����������ڵ㲻��(�߲���Ҫ��ʾ)
	   //			 //��ʾ������
	   //			 //TODO
	   //		 }
	   //		 if (behalf_i != behalf_j) {//�ڲ�ͬ����
	   //			 //�ж���û���ĸ�������
	   //			 if (point_much[parent[i]] && point_much[parent[j]]) { //��������㶼��(���ô��������)
	   //				 //��ʾpoint[behalf_i]��point[behalf_j]
	   //			 }
	   //			 else if (point_much[parent[i]] && !point_much[parent[j]]) {
	   //				 //��ʾpoint[behalf_i]��point[j]
	   //			 }
	   //			 else if (!point_much[parent[i]] && point_much[parent[j]]) {
	   //				 //��ʾpoint[i]��point[behalf_j]
	   //			 }
	   //			 else {//��������㶼��(ֱ������)
	   //				 //��ʾpoint[i]��point[j]
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
		if (x > 16 || x < 1 || y < 1 || y>16) {//�㲻����Ч������
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
				//����v��u֮����ߣ�p[v],p[u];!!!
			}
		}
	}
}
void Graph::update_flow() {//���³�����
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
				//Ҫ��
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