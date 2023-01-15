#pragma once

#include "Vec3.h"
#include "Triangle.h"


static constexpr int N_MESH_VERTICES = 8;
static constexpr int N_MESH_FACES = (6 * 2);

extern Vec3 meshVertices[N_MESH_VERTICES];
extern TriangleFace meshFaces[N_MESH_FACES];



