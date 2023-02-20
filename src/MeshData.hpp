#pragma once

#include <vector>
#include "Vec3.h"
#include "Triangle.h"

struct MeshData {
    std::vector<vec3> vertices;
    std::vector<TriangleFace> faces;
};
