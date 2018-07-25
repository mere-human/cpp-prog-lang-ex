/*
[2] (*3.5) Implement a simple graphics system using whatever graphics facilities
are available on your system (if you don’t hav e a good graphics system or have
no experience with one, you might consider a simple "huge bit ASCII 
implementation" where a point is a character position and you write by placing
a suitable character, such as ∗ in a position):

Window(n,m) creates an area of size n times m on the screen. 
Points on the screen are addressed using (x,y) coordinates (Cartesian). 
A Window w has a current position w.current().
Initially, current is Point(0,0). The current position can be set by 
w.current(p) where p is a Point. 

A Point is specified by a coordinate pair: Point(x,y). 
A Line is specified by a pair of Points: Line(w.current(),p2); 
class Shape is the common interface to Dots, Lines, Rectangles, Circles, etc. 
A Point is not a Shape. 
A Dot, Dot(p) can be used to represent a Point p on the screen.

A Shape is invisible unless draw()n. For example: 
w.draw(Circle(w.current(),10)). 

Every Shape has 9 contact points: e (east), w (west), n (north), s (south),
ne, nw, se, sw, and c (center). 
For example, Line(x.c(),y.nw()) creates a line from x’s center to y’s 
top left corner. 
After draw()ing a Shape the current position is the Shape’s se(). 

A Rectangle is specified by its bottom left and top right corner:
Rectangle(w.current(),Point(10,10)).

As a simple test, display a simple "child’s drawing of a house" with a roof,
two windows, and a door
*/

#include "WinApp.h"
#include <vector>

struct Point
{
	int x;
	int y;
};

class Shape
{
public:
	virtual ~Shape() {}

	virtual Point e() const = 0;
	virtual Point w() const = 0;
	virtual Point n() const = 0;
	virtual Point s() const = 0;

	virtual Point ne() const = 0;
	virtual Point nw() const = 0;
	virtual Point se() const = 0;
	virtual Point sw() const = 0;

	virtual Point c() const = 0;
};

// TODO: normalization
class Line : public Shape
{
	Point a;
	Point b;
public:
	Line(const Point& start, const Point& end)
		: a{ start }, b{ end }
	{}

	Point e() const override { return b; }
	Point w() const override { return a; }
	Point n() const override { return {}; }
	Point s() const override { return {}; }

	Point ne() const override { return {}; }
	Point nw() const override { return {}; }
	Point se() const override { return {}; }
	Point sw() const override { return {}; }

	Point c() const override { return {}; }
};

class Dot : public Shape
{
	Point p;
public:
	Dot(const Point& pt)
		: p{ pt }
	{}

	Point e() const override { return {}; }
	Point w() const override { return {}; }
	Point n() const override { return {}; }
	Point s() const override { return {}; }

	Point ne() const override { return {}; }
	Point nw() const override { return {}; }
	Point se() const override { return {}; }
	Point sw() const override { return {}; }

	Point c() const override { return p; }
};

// TODO: normalization
class Rectangle : public Shape
{
	Point top_right;
	Point bottom_left;
public:
	Rectangle(const Point& top_right_, const Point& bottom_left_)
		: top_right{ top_right_ }, bottom_left{ bottom_left_ }
	{}

	Point e() const override { return {}; }
	Point w() const override { return {}; }
	Point n() const override { return {}; }
	Point s() const override { return {}; }

	Point ne() const override { return {}; }
	Point nw() const override { return top_right; }
	Point se() const override { return bottom_left; }
	Point sw() const override { return {}; }

	Point c() const override { return {}; }
};

class Window
{
	using Polyline = std::vector<Point>;
	std::vector<Polyline> objects;
	windows::WindowHandle handle = nullptr;
	Point pos;
	int h;
	int w;
	void on_redraw()
	{
		for (const auto& obj : objects)
		{
			for (size_t i = 1; i < obj.size(); ++i)
			{
				const auto& start = obj[i - 1];
				const auto& end = obj[i - 1];
				windows::DrawLine(handle, start.x, start.y,
					end.x, end.y);
			}
		}
		
	}
public:
	Window(int height, int width)
		: h{ height }, w{ width }
	{
		handle = windows::WindowNew("Title", w, h);
	}
	const Point& current() const
	{
		return pos;
	}
	void current(const Point& pt)
	{
		windows::WindowMove(handle, pt.x-pos.x, pt.y-pos.y);
		pos = pt;
	}
	// drawing: transform a shape to array of points and later show
	void draw(const Shape& shape)
	{
		// TODO
	}
	void draw(const Line& line)
	{
		objects.push_back({ line.w(), line.e() });
	}
	void draw(const Rectangle& rect)
	{
		// TODO
	}
	void show()
	{
		auto callback = [this]() { on_redraw(); };
		windows::WindowShow(handle, callback);
	}
};

int main()
{
	// TODO: figure out where to put platform-specific code and how to integrate it with these classes.
	// Win32:
	// I do not want to change subsystem from console to windows.
	// I do want to use same project settings for each example.
	// So, probably, it will be just a console which spawns a GUI window.
	// However, it could be done easier if the whole project uses CMake.
	// Then each directory could have it's own settings, etc.

	if (!windows::InitApp())
		return 1;
	Window w(200, 200);
	w.draw(Line({ 10, 10 }, { 30, 30 }));
	w.show();
	windows::RunMessageLoop();
	return 0;
}