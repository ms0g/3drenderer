#include "Clipping.h"
#include <cmath>
#include "Constants.hpp"
#include "Triangle.hpp"


///////////////////////////////////////////////////////////////////////////////
// Frustum planes are defined by a point and a normal vector
///////////////////////////////////////////////////////////////////////////////
// Near plane   :  P=(0, 0, znear), N=(0, 0,  1)
// Far plane    :  P=(0, 0, zfar),  N=(0, 0, -1)
// Top plane    :  P=(0, 0, 0),     N=(0, -cos(fov/2), sin(fov/2))
// Bottom plane :  P=(0, 0, 0),     N=(0, cos(fov/2), sin(fov/2))
// Left plane   :  P=(0, 0, 0),     N=(cos(fov/2), 0, sin(fov/2))
// Right plane  :  P=(0, 0, 0),     N=(-cos(fov/2), 0, sin(fov/2))
///////////////////////////////////////////////////////////////////////////////
//
//           /|\
//         /  | |
//       /\   | |
//     /      | |
//  P*|-->  <-|*|   ----> +z-axis
//     \      | |
//       \/   | |
//         \  | |
//           \|/
//
///////////////////////////////////////////////////////////////////////////////
void Frustum::InitializePlanes() {
    float cos_half_fovX = cos(FOV_X / 2);
    float sin_half_fovX = sin(FOV_X / 2);
    float cos_half_fovY = cos(FOV_Y / 2);
    float sin_half_fovY = sin(FOV_Y / 2);

    m_planes[FRUSTUM::LEFT_PLANE].point = {0, 0, 0};
    m_planes[FRUSTUM::LEFT_PLANE].normal.x = cos_half_fovX;
    m_planes[FRUSTUM::LEFT_PLANE].normal.y = 0;
    m_planes[FRUSTUM::LEFT_PLANE].normal.z = sin_half_fovX;

    m_planes[FRUSTUM::RIGHT_PLANE].point = {0, 0, 0};
    m_planes[FRUSTUM::RIGHT_PLANE].normal.x = -cos_half_fovX;
    m_planes[FRUSTUM::RIGHT_PLANE].normal.y = 0;
    m_planes[FRUSTUM::RIGHT_PLANE].normal.z = sin_half_fovX;

    m_planes[FRUSTUM::TOP_PLANE].point = {0, 0, 0};
    m_planes[FRUSTUM::TOP_PLANE].normal.x = 0;
    m_planes[FRUSTUM::TOP_PLANE].normal.y = -cos_half_fovY;
    m_planes[FRUSTUM::TOP_PLANE].normal.z = sin_half_fovY;

    m_planes[FRUSTUM::BOTTOM_PLANE].point = {0, 0, 0};
    m_planes[FRUSTUM::BOTTOM_PLANE].normal.x = 0;
    m_planes[FRUSTUM::BOTTOM_PLANE].normal.y = cos_half_fovY;
    m_planes[FRUSTUM::BOTTOM_PLANE].normal.z = sin_half_fovY;

    m_planes[FRUSTUM::NEAR_PLANE].point = {0, 0, ZNEAR};
    m_planes[FRUSTUM::NEAR_PLANE].normal.x = 0;
    m_planes[FRUSTUM::NEAR_PLANE].normal.y = 0;
    m_planes[FRUSTUM::NEAR_PLANE].normal.z = 1;

    m_planes[FRUSTUM::FAR_PLANE].point = {0, 0, ZFAR};
    m_planes[FRUSTUM::FAR_PLANE].normal.x = 0;
    m_planes[FRUSTUM::FAR_PLANE].normal.y = 0;
    m_planes[FRUSTUM::FAR_PLANE].normal.z = -1;
}

void Frustum::StartClipping(polygon_t& p) {
    ClipPolygonAgainstPlane(p, FRUSTUM::LEFT_PLANE);
    ClipPolygonAgainstPlane(p, FRUSTUM::RIGHT_PLANE);
    ClipPolygonAgainstPlane(p, FRUSTUM::TOP_PLANE);
    ClipPolygonAgainstPlane(p, FRUSTUM::BOTTOM_PLANE);
    ClipPolygonAgainstPlane(p, FRUSTUM::NEAR_PLANE);
    ClipPolygonAgainstPlane(p, FRUSTUM::FAR_PLANE);
}

void Frustum::ClipPolygonAgainstPlane(polygon_t& p, int plane) {
    vec3 planePoint = m_planes[plane].point;
    vec3 planeNormal = m_planes[plane].normal;

    // Declare a static array of inside vertices that will be part of the final polygon returned via parameter
    vec3 insideVertices[MAX_NUM_POLY_VERTICES];
    int numInsideVertices = 0;

    // Start current and previous vertex with the first and last polygon vertices
    vec3* currentVertex = &p.vertices[0];
    vec3* previousVertex = &p.vertices[p.numVertices - 1];

    // Calculate the dot product of the current and previous vertex
    float currentDot;
    float previousDot = (*previousVertex - planePoint).Dot(planeNormal);

    // Loop all the polygon vertices while the current is different than the last one
    while (currentVertex != &p.vertices[p.numVertices]) {
        currentDot = (*currentVertex - planePoint).Dot(planeNormal);

        // If we changed from inside to outside or from outside to inside
        if (currentDot * previousDot < 0) {
            // Find the interpolation factor t
            float t = previousDot / (previousDot - currentDot);

            // Calculate the intersection point I = Q1 + t(Q2-Q1)
            vec3 intersectionPoint = *currentVertex;    // I =        Qc
            intersectionPoint -= *previousVertex;      // I =       (Qc-Qp)
            intersectionPoint *= t;                     // I =      t(Qc-Qp)
            intersectionPoint += *previousVertex;       // I = Qp + t(Qc-Qp)

            // Insert the intersection point to the list of "inside vertices"
            insideVertices[numInsideVertices++] = intersectionPoint;

        }
        // Current vertex is inside the plane
        if (currentDot > 0) {
            insideVertices[numInsideVertices++] = *currentVertex;
        }

        // Move to the next vertex
        previousDot = currentDot;
        previousVertex = currentVertex;
        ++currentVertex;
    }

    // At the end, copy the list of inside vertices into the destination polygon (out parameter)
    for (int i = 0; i < numInsideVertices; i++) {
        p.vertices[i] = insideVertices[i];
    }
    p.numVertices = numInsideVertices;

}


polygon_t polygon_t::FromTriangle(vec3 v0, vec3 v1, vec3 v2) {
    return {{v0, v1, v2}, 3};
}


void polygon_t::TrianglesFromPolygon(polygon_t& p, Triangle* triangles, int& numTriangles) {
    for (int i = 0; i < p.numVertices - 2; i++) {
        int index0 = 0;
        int index1 = i + 1;
        int index2 = i + 2;

        triangles[i].points[0] = vec4::FromVec3(p.vertices[index0]);
        triangles[i].points[1] = vec4::FromVec3(p.vertices[index1]);
        triangles[i].points[2] = vec4::FromVec3(p.vertices[index2]);
    }
    numTriangles = p.numVertices - 2;
}
