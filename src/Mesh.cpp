#include "Mesh.h"
#include "MeshData.hpp"


void Mesh::SetData(MeshData& meshData) {
    m_rotation = {0, 0, 0};
    m_translation = {0, 0, 0};
    m_scale = {1.0, 1.0, 1.0};

    // Fill vertices
    m_vertices = meshData.vertices;

    // Fill faces
    m_faces = meshData.faces;

}

std::vector<TriangleFace>& Mesh::GetFaces() {
    return m_faces;
}

std::vector<Vec3>& Mesh::GetVertices() {
    return m_vertices;
}

void Mesh::UpdateRotation(float angle) {
    UpdateRotationX(angle);
    UpdateRotationY(angle);
    UpdateRotationZ(angle);
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

float Mesh::GetRotationX() const {
    return m_rotation.x;
}

float Mesh::GetRotationY() const {
    return m_rotation.y;
}

float Mesh::GetRotationZ() const {
    return m_rotation.z;
}

void Mesh::SetRotationX(float angle) {
    m_rotation.x = angle;
}

void Mesh::SetRotationY(float angle) {
    m_rotation.y = angle;
}

void Mesh::SetRotationZ(float angle) {
    m_rotation.z = angle;
}

void Mesh::UpdateScale(float scalar) {
    UpdateScaleX(scalar);
    UpdateScaleY(scalar);
    UpdateScaleZ(scalar);
}

void Mesh::UpdateScaleX(float scalar) {
    m_scale.x += scalar;
}

void Mesh::UpdateScaleY(float scalar) {
    m_scale.y += scalar;
}

void Mesh::UpdateScaleZ(float scalar) {
    m_scale.z += scalar;
}

float Mesh::GetScaleX() const {
    return m_scale.x;
}

float Mesh::GetScaleY() const {
    return m_scale.y;
}

float Mesh::GetScaleZ() const {
    return m_scale.z;
}

void Mesh::SetScaleX(float scalar) {
    m_scale.x = scalar;
}

void Mesh::SetScaleY(float scalar) {
    m_scale.y = scalar;
}

void Mesh::SetScaleZ(float scalar) {
    m_scale.z = scalar;
}

void Mesh::UpdateTranslation(float coord) {
    UpdateTranslationX(coord);
    UpdateTranslationY(coord);
    UpdateTranslationZ(coord);
}

void Mesh::UpdateTranslationX(float coord) {
    m_translation.x += coord;
}

void Mesh::UpdateTranslationY(float coord) {
    m_translation.y += coord;
}

void Mesh::UpdateTranslationZ(float coord) {
    m_translation.z += coord;
}

float Mesh::GetTranslationX() const {
    return m_translation.x;
}

float Mesh::GetTranslationY() const {
    return m_translation.y;
}

float Mesh::GetTranslationZ() const {
    return m_translation.z;
}

void Mesh::SetTranslationX(float coord) {
    m_translation.x = coord;
}

void Mesh::SetTranslationY(float coord) {
    m_translation.y = coord;
}

void Mesh::SetTranslationZ(float coord) {
    m_translation.z = coord;
}
