#include "Mesh.h"


void Mesh::SetData(std::vector<Vec3>& vertices, std::vector<TriangleFace>& faces) {
    m_rotation = {0, 0, 0};

    // Fill vertices
    m_vertices = vertices;

    // Fill faces
    m_faces = faces;

}

void Mesh::UpdateRotation(float angle) {
    UpdateRotationX(angle);
    UpdateRotationY(angle);
    UpdateRotationZ(angle);
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

void Mesh::UpdateRotationX(float angle) {
    m_rotation.x += angle;
}

void Mesh::UpdateRotationY(float angle) {
    m_rotation.y += angle;
}

void Mesh::UpdateRotationZ(float angle) {
    m_rotation.z += angle;
}
