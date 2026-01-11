#include <algorithm>
#include <vector>

#include <lodepng.h>

#include "mesh.h"

int main(int argc, char** argv)
{
    const size_t width = 1000;
    const size_t height = 1000;

    unsigned char* frame = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 4);

    std::fill(frame, frame + width * height * 4, 0xFF);

    Mesh::Graph* graph = new Mesh::Graph();

    graph->add_point(width / 2, height / 2);

    for (const Mesh::Point* point : graph->get_points())
    {
        const size_t index = (point->y * width + point->x) * 4;

        frame[index] = 0;
        frame[index + 1] = 0;
        frame[index + 2] = 0;
    }

    std::vector<unsigned char> data;

    lodepng::encode(data, frame, width, height);
    lodepng::save_file(data, "out.png");

    free(frame);

    return 0;
}
