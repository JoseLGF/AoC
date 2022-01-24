#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>


struct Point
{
    int x;
    int y;

    Point() {}

    Point(int a, int b) {
        x = a;
        y = b;
    }
};

bool operator== (const Point &lhs, const Point &rhs)
{
    return ( (lhs.x == rhs.x) && (lhs.y == rhs.y) );

}

struct {
    bool operator()(Point a, Point b) {
        if (a.x < b.x)
            return true;
        if (a.x > b.x)
            return false;
        if (a.y < b.y)
            return true;
        return false;
    }
} PointCompare;

struct LineSegment
{
    Point p1;
    Point p2;
    LineSegment(int a, int b, int c, int d) {
        p1.x = a;
        p1.y = b;
        p2.x = c;
        p2.y = d;
    }

    bool isHorizontal() {
        return p1.y == p2.y;
    }

    bool isVertical() {
        return p1.x == p2.x;
    }

    void print() {
        std::cout << "line: " << p1.x << ", " << p1.y << " -> " << p2.x << ", " << p2.y << std::endl;
    }
};

void day05()
{
    std::ifstream infile("input/day05.txt");

    // Get all line segments
    std::vector<LineSegment> lines {};
    int x1, y1, x2, y2;
    std::string arrow;
    char comma;
    while (infile >> x1 >> comma >> y1 >> arrow >> x2 >> comma >> y2) {
        lines.push_back(LineSegment(x1,y1,x2,y2));
    }
    /*
    std::cout << "Parsed " << lines.size() << " lines." << std::endl;
    for(auto line: lines) {
        line.print();
    }
    */

    // Get all intermediate points
    std::vector<Point> intermediate_points {};
    for (auto line: lines) {
        if (line.isHorizontal()) {
            int ycord = line.p1.y;
            int xmin = std::min(line.p1.x, line.p2.x);
            int xmax = std::max(line.p1.x, line.p2.x);
            for (int i=xmin; i<=xmax; i++) {
                intermediate_points.push_back(Point(i, ycord));
            }
        }
        if (line.isVertical()) {
            int xcord = line.p1.x;
            int ymin = std::min(line.p1.y, line.p2.y);
            int ymax = std::max(line.p1.y, line.p2.y);
            for (int i=ymin; i<=ymax; i++) {
                intermediate_points.push_back(Point(xcord, i));
            }
        }
    }

    /*
    std::cout << "Before sorting:" << std::endl;
    std::cout << intermediate_points.size() << " points." << std::endl;
    for (auto point : intermediate_points) {
        std::cout << point.x << ", " << point.y << std::endl;
    }
    */

    // sort the points based on one column, and then on the second.
    std::sort(intermediate_points.begin(), intermediate_points.end(), PointCompare);
    /*
    std::cout << "After sorting:" << std::endl;
    std::cout << intermediate_points.size() << " points." << std::endl;
    for (auto point : intermediate_points) {
        std::cout << point.x << ", " << point.y << std::endl;
    }
    */

    // Iterate the sorted points, and count duplicates
    std::vector<Point> duplicate_points;
    for(int i = 0; i < intermediate_points.size() - 1; i++) {
        if (intermediate_points[i] == intermediate_points[i+1]) {
            if (
                    (duplicate_points.empty()) ||
                    (! (intermediate_points[i+1] == duplicate_points.back()) )
            )
            {
                duplicate_points.push_back(intermediate_points[i+1]);
            }
        }
    }

    /*
    std::cout << "Taking only duplicate points:" << std::endl;
    for (auto point : duplicate_points) {
        std::cout << point.x << ", " << point.y << std::endl;
    }
    std::cout << duplicate_points.size() << std::endl;
    */

    // Display final results
    std::cout << "Day 5:" << std::endl;
    std::cout << duplicate_points.size() << std::endl;
    std::cout << -1 << std::endl;
}
