#include "Mesh.h"


void Mesh::SetData(std::vector<Vec3>& vertices, std::vector<TriangleFace>& faces) {
    m_rotation = {0, 0, 0};

    // Fill vertices
    m_vertices = vertices;

    // Fill faces
    m_faces = faces;

}

void Mesh::UpdateRotation(float angle) {
    m_rotation.x += angle;
    m_rotation.y += angle;
    m_rotation.z += angle;
}

std::vector<TriangleFace>& Mesh::GetFaces() {
    return m_faces;
}

std::vector<Vec3>& Mesh::GetVertices() {
    return m_vertices;
}

float Mesh::GetRotationX() const {
    return m_rotation.x;
}

float Mesh::GetRotationY() const {
    return m_rotation.y;
}

float Mesh::GetRotationZ() const {
    return m_rotation.z;
}
