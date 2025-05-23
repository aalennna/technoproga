#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <math.h>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Point {
public:
    Point(double x, double y) : x(x), y(y) {}
    virtual ~Point() = default;

    virtual void draw() const = 0;
    virtual void erase() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;

protected:
    double x, y;
};

class Parallelogram : public Point {
public:
    Parallelogram(double x, double y, double w, double h, double angle)
        : Point(x, y), width(w), height(h), angle(angle) {}

    void draw() const override {
        double rad = angle * M_PI / 180.0;
        double dx = width / 2.0;
        double dy = height / 2.0;
        double dx1 = dx * cos(rad);
        double dy1 = dx * sin(rad);
        double dx2 = -dy * sin(rad);
        double dy2 = dy * cos(rad);
        double x1 = x - dx1 - dx2;
        double y1 = y - dy1 - dy2;
        double x2 = x + dx1 - dx2;
        double y2 = y + dy1 - dy2;
        double x3 = x + dx1 + dx2;
        double y3 = y + dy1 + dy2;
        double x4 = x - dx1 + dx2;
        double y4 = y - dy1 + dy2;

        cout << "Parallelogram vertices:" << endl;
        cout << "(" << x1 << ", " << y1 << ")" << endl;
        cout << "(" << x2 << ", " << y2 << ")" << endl;
        cout << "(" << x3 << ", " << y3 << ")" << endl;
        cout << "(" << x4 << ", " << y4 << ")" << endl;
    }

    void erase() const override {
        cout << "Erasing Parallelogram" << endl;
    }

    void move(double dx, double dy) override {
        x += dx;
        y += dy;
    }

    void rotate(double angleDeg) override {
        angle += angleDeg;
    }

protected:
    double width, height;
    double angle;
};

class Rectangle : public Parallelogram {
public:
    Rectangle(double x, double y, double w, double h)
        : Parallelogram(x, y, w, h, 90.0) {}

    void draw() const override {
        cout << "Rectangle vertices:" << endl;
        Parallelogram::draw();
    }

    void erase() const override {
        cout << "Erasing Rectangle" << endl;
    }
};

class Square : public Parallelogram {
public:
    Square(double x, double y, double side)
        : Parallelogram(x, y, side, side, 90.0) {}

    void draw() const override {
        cout << "Square vertices:" << endl;
        Parallelogram::draw();
    }

    void erase() const override {
        cout << "Erasing Square" << endl;
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(double x, double y, double side, double angle)
        : Parallelogram(x, y, side, side, angle) {}

    void draw() const override {
        cout << "Rhombus vertices:" << endl;
        Parallelogram::draw();
    }

    void erase() const override {
        cout << "Erasing Rhombus" << endl;
    }
};

class Line : public Point {
public:
    Line(double x1, double y1, double x2, double y2)
        : Point(x1, y1), x2(x2), y2(y2) {}

    void draw() const override {
        cout << "Line from (" << x << ", " << y << ") to (" << x2 << ", " << y2 << ")" << endl;
    }

    void erase() const override {
        cout << "Erasing Line" << endl;
    }

    void move(double dx, double dy) override {
        x += dx; y += dy;
        x2 += dx; y2 += dy;
    }

    void rotate(double angleDeg) override {
        double rad = angleDeg * M_PI / 180.0;
        double cx = (x + x2) / 2;
        double cy = (y + y2) / 2;

        double nx = cos(rad) * (x - cx) - sin(rad) * (y - cy) + cx;
        double ny = sin(rad) * (x - cx) + cos(rad) * (y - cy) + cy;
        double nx2 = cos(rad) * (x2 - cx) - sin(rad) * (y2 - cy) + cx;
        double ny2 = sin(rad) * (x2 - cx) + cos(rad) * (y2 - cy) + cy;

        x = nx; y = ny;
        x2 = nx2; y2 = ny2;
    }

private:
    double x2, y2;
};

int main() {
    vector<unique_ptr<Point>> shapes;

    shapes.emplace_back(make_unique<Parallelogram>(2, 2, 10, 15, 40));
    shapes.emplace_back(make_unique<Line>(0, 0, 10, 10));
    shapes.emplace_back(make_unique<Rectangle>(0, 0, 20, 10));
    shapes.emplace_back(make_unique<Square>(5, 5, 15));
    shapes.emplace_back(make_unique<Rhombus>(2, 2, 10, 60));

    for (const auto& shape : shapes) {
        shape->draw();
        shape->move(1, 1);
        shape->rotate(15);
        shape->draw();
        shape->erase();
        cout << endl;
    }

    return 0;
}