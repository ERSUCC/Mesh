#include "mesh.h"

namespace Mesh
{
    float angle_dist(const float a0, const float a1)
    {
        const float dist = fabsf(a1 - a0);

        if (dist > M_PI)
        {
            return M_PI * 2 - dist;
        }

        return dist;
    }

    Point::Point(const float x, const float y) :
        x(x), y(y) {}

    Triangle::Triangle(const size_t p0, const size_t p1, const size_t p2) :
        p0(p0), p1(p1), p2(p2) {}

    Edge::Edge(const size_t p0, const size_t p1) :
        p0(p0), p1(p1) {}

    Graph::Graph()
    {
        points =
        {
            new Point(0, -100000),
            new Point(100000, 100000),
            new Point(-100000, 100000)
        };
    }

    void Graph::add_point(const float x, const float y)
    {
        const size_t index = points.size();

        Point* point = new Point(x, y);

        points.push_back(point);

        for (int i = triangles.size() - 1; i >= 0; i--)
        {
            const size_t i0 = triangles[i]->p0;
            const size_t i1 = triangles[i]->p1;
            const size_t i2 = triangles[i]->p2;

            const Point* p0 = points[i0];
            const Point* p1 = points[i1];
            const Point* p2 = points[i2];

            const float a0 = atan2f(p0->y - point->y, p0->x - point->x);
            const float a1 = atan2f(p1->y - point->y, p1->x - point->x);
            const float a2 = atan2f(p2->y - point->y, p2->x - point->x);

            if (angle_dist(a0, a1) + angle_dist(a1, a2) + angle_dist(a2, a0) >= M_PI * 2)
            {
                remove_triangle(triangles[i]);

                add_triangle(index, i0, i1);
                add_triangle(index, i1, i2);
                add_triangle(index, i2, i0);

                add_edge(index, i0);
                add_edge(index, i1);
                add_edge(index, i2);

                break;
            }
        }

        bool flipped;

        do
        {
            flipped = false;

            for (size_t i = 0; i < edges.size(); i++)
            {
                const size_t e0 = edges[i]->p0;
                const size_t e1 = edges[i]->p1;

                std::vector<size_t> shared;

                for (size_t j = 0; j < triangles.size(); j++)
                {
                    const size_t t0 = triangles[j]->p0;
                    const size_t t1 = triangles[j]->p1;
                    const size_t t2 = triangles[j]->p2;

                    if ((e0 == t0 || e0 == t1 || e0 == t2) && (e1 == t0 || e1 == t1 || e1 == t2))
                    {
                        shared.push_back(j);

                        if (shared.size() == 2)
                        {
                            break;
                        }
                    }
                }

                if (shared.size() == 2)
                {
                    const Triangle* t0 = triangles[shared[0]];
                    const Triangle* t1 = triangles[shared[1]];

                    size_t p0;

                    if (t0->p0 != e0 && t0->p0 != e1)
                    {
                        p0 = t0->p0;
                    }

                    else if (t0->p1 != e0 && t0->p1 != e1)
                    {
                        p0 = t0->p1;
                    }

                    else
                    {
                        p0 = t0->p2;
                    }

                    size_t p1;

                    if (t1->p0 != e0 && t1->p0 != e1)
                    {
                        p1 = t1->p0;
                    }

                    else if (t1->p1 != e0 && t1->p1 != e1)
                    {
                        p1 = t1->p1;
                    }

                    else
                    {
                        p1 = t1->p2;
                    }

                    const float a0 = atan2f(points[e0]->y - points[p0]->y, points[e0]->x - points[p0]->x);
                    const float a1 = atan2f(points[e1]->y - points[p0]->y, points[e1]->x - points[p0]->x);
                    const float a2 = atan2f(points[e0]->y - points[p1]->y, points[e0]->x - points[p1]->x);
                    const float a3 = atan2f(points[e1]->y - points[p1]->y, points[e1]->x - points[p1]->x);

                    if (angle_dist(a0, a1) + angle_dist(a2, a3) > M_PI)
                    {
                        remove_triangle(t0);
                        remove_triangle(t1);

                        remove_edge(edges[i]);

                        add_triangle(p0, e0, p1);
                        add_triangle(p0, e1, p1);

                        add_edge(p0, p1);

                        flipped = true;

                        break;
                    }
                }
            }
        } while (flipped);
    }

    std::vector<Point*> Graph::get_points() const
    {
        std::vector<Point*> final_points;

        for (size_t i = 3; i < points.size(); i++)
        {
            final_points.push_back(points[i]);
        }

        return final_points;
    }

    void Graph::add_triangle(const size_t p0, const size_t p1, const size_t p2)
    {
        std::vector<size_t> ps = { p0, p1, p2 };

        std::sort(ps.begin(), ps.end());

        triangles.push_back(new Triangle(ps[0], ps[1], ps[2]));
    }

    void Graph::remove_triangle(const Triangle* t0)
    {
        triangles.erase(std::find_if(triangles.begin(), triangles.end(), [=](const Triangle* t1)
        {
            return t0->p0 == t1->p0 && t0->p1 == t1->p1 && t0->p2 == t1->p2;
        }));
    }

    void Graph::add_edge(const size_t p0, const size_t p1)
    {
        if (p0 <= p1)
        {
            edges.push_back(new Edge(p0, p1));
        }

        else
        {
            edges.push_back(new Edge(p1, p0));
        }
    }

    void Graph::remove_edge(const Edge* e0)
    {
        edges.erase(std::find_if(edges.begin(), edges.end(), [=](const Edge* e1)
        {
            return e0->p0 == e1->p0 && e0->p1 == e1->p1;
        }));
    }
}
