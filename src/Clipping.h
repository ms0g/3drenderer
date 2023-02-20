#pragma once

#include "Vec3.h"
#include "Texture.h"


#define MAX_NUM_POLY_VERTICES 10
#define MAX_NUM_POLY_TRIANGLES MAX_NUM_POLY_VERTICES

enum FRUSTUM {
    LEFT_PLANE,
    RIGHT_PLANE,
    TOP_PLANE,
    BOTTOM_PLANE,
    NEAR_PLANE,
    FAR_PLANE
};

struct plane_t {
    vec3 point;
    vec3 normal;
};

class Triangle;
struct polygon_t {
    vec3 vertices[MAX_NUM_POLY_VERTICES];
    texcoord texcoords[MAX_NUM_POLY_VERTICES];
    int numVertices;

    static polygon_t FromTriangle(vec3 v0, vec3 v1, vec3 v2, texcoord t0, texcoord t1, texcoord t2);

    static void TrianglesFromPolygon(polygon_t& p, Triangle* triangles, int& numTriangles);
};


class Frustum {
public:
    void InitializePlanes();

    void StartClipping(polygon_t& p);

private:
    void ClipPolygonAgainstPlane(polygon_t& p, int plane);

    static constexpr int NUM_PLANES = 6;
    plane_t m_planes[NUM_PLANES];
};

namespace utils {
float lerp(float a, float b, float t);
}
