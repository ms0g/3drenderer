#pragma once

#include <vector>
#include "Vec3.h"
#include "Triangle.h"

struct MeshData {
    std::vector<Vec3> vertices;
    std::vector<TriangleFace> faces;
};
