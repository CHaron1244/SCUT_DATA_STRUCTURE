#include "Point.h"
#include <map>
#include <math.h>
#define eps 1e-8
using namespace std;

int sgn(double x) {
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	else return 1;
}
point::point() {
}
point::point(double a, double b) {
	x = a, y = b;
}
point point:: operator +(const point b) {
	return point(x + b.x, y + b.y);
}
point point:: operator -(const point b) {
	return point(x - b.x, y - b.y);
}
double point::operator *(const point b) {
	return x * b.x + y * b.y;
}
point point::operator *(const double k) {
	return point(x * k, y * k);
}
double point::operator ^(const point b) {
	return x * b.y - y * b.x;
}

Line::Line() {

}
Line::Line(point a, point b) {
	p1 = a, p2 = b;
	p3 = p1 - p2;
}
int cross(point a, point b) {
	return sgn(a ^ b);
}
double dist(point a, point b) {
	return sqrt((a - b) * (a - b));
}
bool judge(Line a, Line b) {
	if (cross(b.p1 - a.p2, a.p3) * cross(b.p2 - a.p2, a.p3) < 0 && cross(a.p1 - b.p2, b.p3) * cross(a.p2 - b.p2, b.p3) < 0) return 1;
	return 0;
}
point meet(Line a, Line b) {
	point c;
	double dis = ((a.p2 - b.p2) ^ (b.p3)) / ((a.p3) ^ (b.p3));
	if (dis < 0) dis = -dis;
	c = a.p2 + a.p3 * dis;
	return c;
}