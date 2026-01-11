#pragma once

#define _USE_MATH_DEFINES

#include <algorithm>
#include <math.h>
#include <vector>

namespace Mesh
{
    float angle_dist(const float a0, const float a1);

    struct Point
    {
        Point(const float x, const float y);

        const float x;
        const float y;
    };

    struct Triangle
    {
        Triangle(const size_t p0, const size_t p1, const size_t p2);

        const size_t p0;
        const size_t p1;
        const size_t p2;
    };

    struct Edge
    {
        Edge(const size_t p0, const size_t p1);

        const size_t p0;
        const size_t p1;
    };

    struct Graph
    {
        Graph();

        void add_point(const float x, const float y);

        std::vector<Point*> get_points() const;

    private:
        void add_triangle(const size_t p0, const size_t p1, const size_t p2);
        void remove_triangle(const Triangle* t0);

        void add_edge(const size_t p0, const size_t p1);
        void remove_edge(const Edge* e0);

        std::vector<Point*> points;
        std::vector<Triangle*> triangles = { new Triangle(0, 1, 2) };
        std::vector<Edge*> edges = { new Edge(0, 1), new Edge(1, 2), new Edge(0, 2) };

    };
}
