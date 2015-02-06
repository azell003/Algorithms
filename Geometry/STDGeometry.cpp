/*
Author: Alfredo Zellek

Standard Geometry Library

This handles basic geometric objects like Points, Lines, Segments, and Circles.
*/


#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-9;

double inline deg2rad(double deg) { return (deg * M_PI / 180.0); }
double inline rad2deg(double rad) { return (rad * 180.0 / M_PI); }

struct Point
{
	double x, y;
	bool empty;

	Point(double _x = 0.0, double _y = 0.0) 
	{
		x = _x;
		y = _y;
		empty = false;
	}

	Point rotateCCW(double angle)
	{
		int new_x = x * cos(angle) - y * sin(angle);
		int new_y = x * sin(angle) + y * cos(angle);
		return Point(new_x, new_y);
	}

	double angle()
	{
		return atan2(y, x);
	}

	double magnitude()
	{
		return sqrt(x * x + y * y);
	}

	Point operator +(const Point &p) const { return Point(x + p.x, y + p.y); }
	Point operator -(const Point &p) const { return Point(x - p.x, y - p.y); }
	Point operator *(double c) const { return Point(c * x, c * y); }
	Point operator /(double c) const { return Point(x / c, y / c); }
	bool operator ==(const Point &p) const
	{
		return fabs(p.x - x) < EPS && fabs(p.y - y) < EPS;
	}

	friend ostream& operator <<(ostream& os, const Point &p) 
	{
		os << "(" << p.x << ", " << p.y << ")";
		return os;
	}
};

double dot(Point p, Point q) { return p.x * q.x + p.y * q.y; }
double cross(Point p, Point q) { return p.x * q.y - p.y * q.x; }
double dist2(Point p, Point q) { return dot(q - p, q - p); }

struct Line
{
	double a, b, c;

	Line(double _a, double _b, double _c)
	{
		a = _a;
		b = _b;
		c = _c;
	}

	Line(Point p, double angle)
	{
		a = sin(angle);
		b = -cos(angle);
		c = -a * p.x - b * p.y;
	}

	Line(Point p, Point q)
	{
		a = q.y - p.y;
		b = -(q.x - p.x);
		c = -a * p.x - b * p.y;
	}

	Line perpendicular(Point p)
	{
		return Line(-b, a, b * p.x - a * p.y);
	}

	bool parallel(Line m) 
	{ 
		return fabs(a * m.b - m.a * b) < EPS; 
	}

	bool contains(Point p)
	{
		return fabs(a * p.x + b * p.y + c) < EPS;
	}

	Point intersection(Line m)
	{
		if(parallel(m))
		{
			Point p;
			p.empty = true;
			return p;
		}
		double det = cross(Point(a, b), Point(m.a, m.b));
		double x = cross(Point(b, c), Point(m.b, m.c)) / det;
		double y = cross(Point(c, a), Point(m.c, m.a)) / det;
		return Point(x, y);
	}

	double dist2pt(Point p)
	{
		Line perpl = perpendicular(p);
		Point inter = intersection(perpl);
		return sqrt(dist2(p, inter));
	}

	double at(double x)
	{
		return (-a / b) * x + (-c / b);
	}

	double value(Point p)
	{
		return a * p.x + b * p.y + c;
	}
};

struct Segment
{
	Point a, b;
	double length2;

	Segment(Point _a, Point _b)
	{
		a = _a;
		b = _b; 
		length2 = dist2(_a, _b);
	}

	double length()
	{
		return sqrt(length2);
	}

	double dist2pt(Point p)
	{
		double len = length(); 
		double left = sqrt(dist2(a, p));
		double right = sqrt(dist2(b, p));
		if((len < EPS) || (right * right > left * left + len * len))
			return left;
		if(left * left > right * right + len * len)
			return right;
		return Line(a, b).dist2pt(p);
	}

	bool contains(Point p, bool boundary)
	{
		Line line = Line(a, b);
		if(a == p || b == p) return boundary;
		if(a == b || !line.contains(p)) return false;
		Line perp = line.perpendicular(a);
		double av = perp.value(a);
		double bv = perp.value(b);
		double pv = perp.value(p);
		return (av < pv && pv < bv) || (bv < pv && pv < av);
	}

	Point intersect(Segment s, bool boundary)
	{
		Line line = Line(a, b);
		Line line2 = Line(s.a, s.b);
		Point inter = line.intersection(line2);
		if(!contains(inter, boundary) || !s.contains(inter, boundary))
			inter.empty = true;
		return inter;
	}
};

struct Circle
{
	Point C;
	double r;
	bool error; // flag for certain operations

	Circle(Point _C, double _r)
	{
		C = _C;
		r = _r;
		error = false;
	}

	Circle(Point a, Point b, Point c)
	{
		Line ab = Line(a, b).perpendicular( (a + b) / 2.0 );
		Line bc = Line(b, c).perpendicular( (b + c) / 2.0 );
		error = ab.parallel(bc);
		if(!error)
			C = ab.intersection(bc);
		r = sqrt(dist2(a, C));
	}
};

int main()
{
	Point a = Point(0, 0);
	Point b = Point(1, 1);
	Segment ab = Segment(a, b);
	cout << ab.dist2pt(Point(1, 0)) << endl;
}
