#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Coord {
    long long x{0}, y{0};
};

struct Line {
    Coord a{}, b{};
};

bool point_on_edge(double x, double y, const std::vector<Line>& edges) {
    for (const auto& e : edges) {
        if (e.a.x == e.b.x) {
            double ex = static_cast<double>(e.a.x);
            if (x == ex) {
                double ymin = std::min(e.a.y, e.b.y);
                double ymax = std::max(e.a.y, e.b.y);
                if (y >= ymin && y <= ymax) {
                    return true;
                }
            }
        } else if (e.a.y == e.b.y) {
            double ey = static_cast<double>(e.a.y);
            if (y == ey) {
                double xmin = std::min(e.a.x, e.b.x);
                double xmax = std::max(e.a.x, e.b.x);
                if (x >= xmin && x <= xmax) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_inside_polygon(double x, double y, const std::vector<Coord>& poly) {
    int n = static_cast<int>(poly.size());

    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        double xi = static_cast<double>(poly[i].x);
        double yi = static_cast<double>(poly[i].y);
        double xj = static_cast<double>(poly[j].x);
        double yj = static_cast<double>(poly[j].y);

        bool intersect = ((yi > y) != (yj > y)) &&
                         (x < (xj - xi) * (y - yi) / (yj - yi) + xi);
        if (intersect) {
            inside = !inside;
        }
    }

    return inside;
}

bool inside_or_on(const std::vector<double>& xs,
                  const std::vector<double>& ys,
                  const std::vector<Line>& edges,
                  const std::vector<Coord>& poly) {
    int n = static_cast<int>(xs.size());

    for (int i = 0; i < n; ++i) {
        double x = xs[i];
        double y = ys[i];

        if (!point_on_edge(x, y, edges) && !is_inside_polygon(x, y, poly)) {
            return false;
        }
    }

    return true;
}

bool rectangle_crosses_polygon(long long x1, long long y1,
                               long long x2, long long y2,
                               const std::vector<Line>& edges) {
    std::vector<Line> rect_sides = {
        {{x1, y1}, {x2, y1}},
        {{x1, y2}, {x2, y2}},
        {{x1, y1}, {x1, y2}},
        {{x2, y1}, {x2, y2}}
    };

    for (const auto& r : rect_sides) {
        bool rect_horizontal = (r.a.y == r.b.y);
        long long r_x1 = r.a.x;
        long long r_y1 = r.a.y;
        long long r_x2 = r.b.x;
        long long r_y2 = r.b.y;

        if (rect_horizontal && r_x1 > r_x2) std::swap(r_x1, r_x2);
        if (!rect_horizontal && r_y1 > r_y2) std::swap(r_y1, r_y2);

        for (const auto& e : edges) {
            bool edge_horizontal = (e.a.y == e.b.y);

            if (rect_horizontal == edge_horizontal) {
                continue;
            }

            if (rect_horizontal) {
                long long y = r_y1;
                long long vx = e.a.x;
                long long vy1 = e.a.y;
                long long vy2 = e.b.y;
                if (vy1 > vy2) std::swap(vy1, vy2);

                if (vx > r_x1 && vx < r_x2 &&
                    y > vy1 && y < vy2) {
                    return true;
                }
            } else {
                long long x = r_x1;
                long long hy = e.a.y;
                long long hx1 = e.a.x;
                long long hx2 = e.b.x;
                if (hx1 > hx2) std::swap(hx1, hx2);

                if (hy > r_y1 && hy < r_y2 &&
                    x > hx1 && x < hx2) {
                    return true;
                }
            }
        }
    }

    return false;
}

long long area_of_largest_rectangle(const std::vector<Coord>& coordinates) {
    int n = static_cast<int>(coordinates.size());

    std::vector<Line> edges;
    edges.reserve(n);
    for (int i = 0; i < n; ++i) {
        Coord a = coordinates[i];
        Coord b = coordinates[(i + 1) % n];
        edges.push_back({a, b});
    }

    long long max_area = 0;

    for (int i = 0; i < n - 1; ++i) {
        const Coord& p = coordinates[i];

        for (int j = i + 1; j < n; ++j) {
            const Coord& q = coordinates[j];

            long long x1 = std::min(p.x, q.x);
            long long x2 = std::max(p.x, q.x);
            long long y1 = std::min(p.y, q.y);
            long long y2 = std::max(p.y, q.y);

            std::vector<double> xs = {
                static_cast<double>(x1),
                static_cast<double>(x1),
                static_cast<double>(x2),
                static_cast<double>(x2)
            };
            std::vector<double> ys = {
                static_cast<double>(y1),
                static_cast<double>(y2),
                static_cast<double>(y1),
                static_cast<double>(y2)
            };

            if (!inside_or_on(xs, ys, edges, coordinates)) {
                continue;
            }

            if (rectangle_crosses_polygon(x1, y1, x2, y2, edges)) {
                continue;
            }

            long long width  = x2 - x1 + 1;
            long long height = y2 - y1 + 1;
            long long area   = width * height;

            if (area > max_area) {
                max_area = area;
            }
        }
    }

    return max_area;
}

int main() {
    std::vector<Coord> coordinates;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream ss(line);
        std::string x_str, y_str;

        if (!std::getline(ss, x_str, ',') ||
            !std::getline(ss, y_str)) {
            continue;
        }

        Coord c;
        c.x = std::stoll(x_str);
        c.y = std::stoll(y_str);
        coordinates.push_back(c);
    }

    std::cout << area_of_largest_rectangle(coordinates) << '\n';
    return 0;
}

