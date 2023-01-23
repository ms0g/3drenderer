#pragma once

#include <vector>
#include "Vec3.h"
#include "Triangle.hpp"

struct MeshData {
    std::vector<Vec3> vertices;
    std::vector<TriangleFace> faces;
};
