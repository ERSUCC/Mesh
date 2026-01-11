#include "graphics.h"

Graphics::Graphics(const size_t width, const size_t height) :
    width(width), height(height)
{
    frame = (uint32_t*)malloc(sizeof(uint32_t) * width * height);

    std::fill(frame, frame + width * height, COLOR(255, 255, 255));
}

Graphics::~Graphics()
{
    free(frame);
}

void Graphics::draw_graph(const Mesh::Graph* graph)
{
    const std::vector<Mesh::Point*> points = graph->get_points();

    for (const Mesh::Edge* edge : graph->get_edges())
    {
        const Mesh::Point* p0 = points[edge->p0];
        const Mesh::Point* p1 = points[edge->p1];

        line(p0->x, p0->y, p1->x, p1->y, COLOR(0, 0, 0));
    }
}

void Graphics::export_frame(const std::string& path) const
{
    unsigned char* expanded = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 4);

    for (size_t i = 0; i < width * height; i++)
    {
        expanded[i * 4] = RED(frame[i]);
        expanded[i * 4 + 1] = GREEN(frame[i]);
        expanded[i * 4 + 2] = BLUE(frame[i]);
        expanded[i * 4 + 3] = 255;
    }

    std::vector<unsigned char> data;

    lodepng::encode(data, expanded, width, height);
    lodepng::save_file(data, path);

    free(expanded);
}

void Graphics::line(int x0, int y0, int x1, int y1, uint32_t color)
{
    const int dx = abs(x1 - x0);
    const int dy = abs(y1 - y0);

    if (dy > dx)
    {
        if (y0 > y1)
        {
            int temp = x0;

            x0 = x1;
            x1 = temp;

            temp = y0;

            y0 = y1;
            y1 = temp;
        }

        int step = 1;

        if (x0 > x1)
        {
            step = -1;
        }

        int d = dx * 2 - dy;
        int x = x0;

        for (int y = y0; y <= y1; y++)
        {
            if (x >= 0 && y >= 0 && x < width && y < height)
            {
                pixel(x, y, color);
            }

            if (d > 0)
            {
                x += step;
                d -= dy * 2;
            }

            d += dx * 2;
        }
    }

    else
    {
        if (x0 > x1)
        {
            int temp = x0;

            x0 = x1;
            x1 = temp;

            temp = y0;

            y0 = y1;
            y1 = temp;
        }

        int step = 1;

        if (y0 > y1)
        {
            step = -1;
        }

        int d = dy * 2 - dx;
        int y = y0;

        for (int x = x0; x <= x1; x++)
        {
            if (x >= 0 && y >= 0 && x < width && y < height)
            {
                pixel(x, y, color);
            }

            if (d > 0)
            {
                y += step;
                d -= dx * 2;
            }

            d += dy * 2;
        }
    }
}
