#ifndef Point_H
#define Point_H

int sgn(double x);
class point {
	public:
		double x, y;
		point();
		point(double a, double b);
		//���캯��
		point operator +(const point b);
		//����+
		point operator -(const point b);
		//����-
		double operator *(const point b);
		//����*����������
		point operator *(const double k);
		//����*���Ŵ�����
		double operator ^(const point b);
		//����^,���������
};
class Line {
	public:
		point p1, p2, p3;
		Line();
		Line(point a, point b);
		//Line�������˵���������
};

//���� 
int cross(point a, point b);
//����֮����� 
double dist(point a, point b);


//���Ϊ0��һ���ཻ���ܹ���  
//�ж��˹����Ƿ��ص�������Ҳ���ཻ�ˣ� 
bool judge(Line a, Line b);

//Ҫ���ж�ƽ�У��ص����ཻ���󽻵㣬��Ȼ���bug������ 
point meet(Line a, Line b);

//����½��ıߺ�ԭ�б��Ƿ��в�������
#endif // !Point.h



