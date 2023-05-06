#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <limits>
#include <unordered_set>
#include <utility>
#include <stack>
#include <set>
#include <queue>
#include <climits>

struct vec2D
{
    int x;
    int y;

    friend std::ostream&
    operator<<(std::ostream& os, const vec2D& v);
};

std::ostream& operator<<(std::ostream& os, const vec2D& v)
{
    os << "(" << v.x << ',' << v.y << ')';
    return os;
}

struct RectArea
{
    int x_min, x_max;
    int y_min, y_max;

    RectArea(int xmin, int xmax, int ymin, int ymax) {
        this->x_min = xmin;
        this->x_max = xmax;
        this->y_min = ymin;
        this->y_max = ymax;
    }

    RectArea() {
        this->x_min = 0;
        this->x_max = 0;
        this->y_min = 0;
        this->y_max = 0;
    }

};

struct World
{
    vec2D probe_position;
    vec2D probe_speed;
    int num_steps;
    RectArea target;
    int highest_pos;

    World(vec2D initial_speed, RectArea target) {
        highest_pos = INT_MIN;
        num_steps = 0;
        probe_position = {0,0};
        probe_speed = initial_speed;
        this->target = target;
    }

    void step() {
        probe_position.x += probe_speed.x;
        probe_position.y += probe_speed.y;

        if (probe_speed.x > 0) {
            probe_speed.x--;
        }
        if (probe_speed.x < 0) {
            probe_speed.x++;
        }

        probe_speed.y--;

        if(probe_position.y > highest_pos) {
            highest_pos = probe_position.y;
        }

        num_steps++;
    }

    bool is_probe_within_target () {
        return
            (probe_position.x >= target.x_min) &&
            (probe_position.x <= target.x_max) &&
            (probe_position.y >= target.y_min) &&
            (probe_position.y <= target.y_max);
    }

    bool is_probe_within_target_x() {
        return
            (probe_position.x >= target.x_min) &&
            (probe_position.x <= target.x_max);
    }

    void print() {
        bool hit = is_probe_within_target();
        std::cout << "Step=" << num_steps
            << ", P=" << probe_position
            << ", V=" << probe_speed;
        if(hit) {
            std::cout << " Hit";
        }
        std::cout << std::endl;
    }

    // Returns true if the probe if we know that the probe
    // can not hit the target
    bool is_exhausted() {
        if (probe_speed.x != 0) {
            return false;
        }
        if (probe_position.y >= target.y_min) {
            return false;
        }
        return true;
    }

    bool simulate_until_hit() {
        while (! is_exhausted()) {
            if (is_probe_within_target()) {
                return true;
            }
            step();
        }
        return false;
    }

};

void day17(std::string& input_path)
{
    int part_1_solution = -1;
    int part_2_solution = -1;

    // Init
    int xmin = 257;
    int xmax = 286;
    int ymin = -101;
    int ymax = -57;
    int global_vy_max = INT_MIN;
    int global_y_max = INT_MIN;
    int distinct_hits= 0;
    for (int vx=0; vx<=xmax; vx++) {
        for (int vy=ymin; vy<=xmax; vy++) {
            World world(
                    vec2D(vx,vy),
                    RectArea(xmin,xmax,ymin,ymax)
                    );
            if (world.simulate_until_hit()) {
                distinct_hits++;
                if (vy > global_vy_max) {
                    global_vy_max = vy;
                    global_y_max = world.highest_pos;
                }
            }
        }
    }

    // Part 1
    part_1_solution = global_y_max;

    // Part 2
    part_2_solution = distinct_hits;

    // Display final results
    std::cout << "Day 17:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
