#pragma once

#include <random>
#include <chrono>

#include "graphics.h"
#include "mesh.h"

struct Test
{
    Test();

    void test_all();

private:
    const size_t width = 1000;
    const size_t height = 1000;

    Graphics* graphics;

};
