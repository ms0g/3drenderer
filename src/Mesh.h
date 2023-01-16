#pragma once

#include <vector>
#include "Vec3.h"
#include "Triangle.h"


static constexpr int N_CUBE_VERTICES = 8;
static constexpr int N_CUBE_FACES = (6 * 2);

extern Vec3 cubeVertices[N_CUBE_VERTICES];
extern TriangleFace cubeFaces[N_CUBE_FACES];


template<size_t vertexCount = 0, size_t faceCount = 0>
class Mesh {
public:
    Mesh(Vec3* vertices, TriangleFace* faces, Vec3 rotation);

    void UpdateRotation(float angle);

    [[nodiscard]] std::vector<TriangleFace>& GetFaces();

    [[nodiscard]] std::vector<Vec3>& GetVertices();

    [[nodiscard]] float GetRotationX() const;

    [[nodiscard]] float GetRotationY() const;

    [[nodiscard]] float GetRotationZ() const;


private:
    Vec3 m_rotation;
    std::vector<Vec3> m_vertices;
    std::vector<TriangleFace> m_faces;
};

template<size_t vertexCount, size_t faceCount>
Mesh<vertexCount, faceCount>::Mesh(Vec3* vertices, TriangleFace* faces, Vec3 rotation) {
    m_rotation = rotation;
    // Fill vertices
    for (int i = 0; i < vertexCount; ++i) {
        auto vertex = vertices[i];
        m_vertices.emplace_back(vertex);
    }

    // Fill faces
    for (int i = 0; i < faceCount; ++i) {
        auto face = faces[i];
        m_faces.emplace_back(face);
    }
}

template<size_t vertexCount, size_t faceCount>
void Mesh<vertexCount, faceCount>::UpdateRotation(float angle) {
    m_rotation.x += angle;
    m_rotation.y += angle;
    m_rotation.z += angle;
}

template<size_t vertexCount, size_t faceCount>
std::vector<TriangleFace>& Mesh<vertexCount, faceCount>::GetFaces() {
    return m_faces;
}

template<size_t vertexCount, size_t faceCount>
std::vector<Vec3>& Mesh<vertexCount, faceCount>::GetVertices() {
    return m_vertices;
}

template<size_t vertexCount, size_t faceCount>
float Mesh<vertexCount, faceCount>::GetRotationX() const {
    return m_rotation.x;
}

template<size_t vertexCount, size_t faceCount>
float Mesh<vertexCount, faceCount>::GetRotationY() const {
    return m_rotation.y;
}

template<size_t vertexCount, size_t faceCount>
float Mesh<vertexCount, faceCount>::GetRotationZ() const {
    return m_rotation.z;
}





