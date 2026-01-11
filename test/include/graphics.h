#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <lodepng.h>

#include <mesh.h>

#define RED(c) (((c) >> 24) & 0xFF)
#define GREEN(c) (((c) >> 16) & 0xFF)
#define BLUE(c) (((c) >> 8) & 0xFF)
#define COLOR(r, g, b) ((((r) & 0xFF) << 24) | (((g) & 0xFF) << 16) | (((b) & 0xFF) << 8) | 0xFF)

struct Graphics
{
    Graphics(const size_t width, const size_t height);
    ~Graphics();

    void draw_graph(const Mesh::Graph* graph);

    void export_frame(const std::string& path) const;

private:
    inline void pixel(const int x, const int y, const uint32_t color)
    {
        frame[y * width + x] = color;
    }

    void line(int x0, int y0, int x1, int y1, uint32_t color);

    const size_t width;
    const size_t height;

    uint32_t* frame;

};
