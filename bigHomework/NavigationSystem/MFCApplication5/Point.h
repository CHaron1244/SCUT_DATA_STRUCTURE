#ifndef Point_H
#define Point_H

int sgn(double x);
class point {
	public:
		double x, y;
		point();
		point(double a, double b);
		//构造函数
		point operator +(const point b);
		//重载+
		point operator -(const point b);
		//重载-
		double operator *(const point b);
		//重载*，算向量积
		point operator *(const double k);
		//重载*，放大向量
		double operator ^(const point b);
		//重载^,做叉积运算
};
class Line {
	public:
		point p1, p2, p3;
		Line();
		Line(point a, point b);
		//Line由两个端点和向量组成
};

//求叉积 
int cross(point a, point b);
//两点之间距离 
double dist(point a, point b);


//叉积为0不一定相交可能共线  
//判断了共线是否重叠（这里也算相交了） 
bool judge(Line a, Line b);

//要先判断平行，重叠和相交再求交点，不然会出bug！！！ 
point meet(Line a, Line b);

//检查新建的边和原有边是否有不合理交点
#endif // !Point.h



