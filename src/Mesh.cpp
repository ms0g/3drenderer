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

const Vec3& Mesh::GetRotation() const {
    return m_rotation;
}

void Mesh::SetRotation(const Vec3& mRotation) {
    m_rotation = mRotation;
}

const Vec3& Mesh::GetScale() const {
    return m_scale;
}

void Mesh::SetScale(const Vec3& mScale) {
    m_scale = mScale;
}

const Vec3& Mesh::GetTranslation() const {
    return m_translation;
}

void Mesh::SetTranslation(const Vec3& mTranslation) {
    m_translation = mTranslation;
}

const std::vector<Vec3>& Mesh::GetVertices() const {
    return m_vertices;
}

void Mesh::SetVertices(const std::vector<Vec3>& mVertices) {
    m_vertices = mVertices;
}

const std::vector<TriangleFace>& Mesh::GetFaces() const {
    return m_faces;
}

void Mesh::SetFaces(const std::vector<TriangleFace>& mFaces) {
    m_faces = mFaces;
}
