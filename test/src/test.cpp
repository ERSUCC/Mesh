#include "test.h"

Test::Test()
{
    graphics = new Graphics(width, height);
}

void Test::test_all()
{
    std::mt19937_64 rng(std::chrono::high_resolution_clock().now().time_since_epoch().count());

    std::uniform_real_distribution<float> xdist(0, width);
    std::uniform_real_distribution<float> ydist(0, height);

    Mesh::Graph* graph = new Mesh::Graph();

    for (size_t i = 0; i < 100; i++)
    {
        graph->add_point(xdist(rng), ydist(rng));
    }

    graphics->draw_graph(graph);
    graphics->export_frame("out.png");
}
