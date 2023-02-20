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


const Texture& Mesh::GetTexture() const {
    return *m_texture;
}


void Mesh::SetTexture(std::unique_ptr<Texture>& tex) {
    m_texture = std::move(tex);
}


const vec3& Mesh::GetRotation() const {
    return m_rotation;
}


void Mesh::SetRotation(const vec3& rotation) {
    m_rotation = rotation;
}


void Mesh::UpdateRotation(const vec3& rotation) {
    m_rotation += rotation;
}


const vec3& Mesh::GetScale() const {
    return m_scale;
}


void Mesh::SetScale(const vec3& scale) {
    m_scale = scale;
}


void Mesh::UpdateScale(const vec3& scale) {
    m_scale += scale;
}


const vec3& Mesh::GetTranslation() const {
    return m_translation;
}


void Mesh::SetTranslation(const vec3& translation) {
    m_translation = translation;
}


void Mesh::UpdateTranslation(const vec3& translation) {
    m_translation += translation;
}


const std::vector<vec3>& Mesh::GetVertices() const {
    return m_vertices;
}


void Mesh::SetVertices(const std::vector<vec3>& vertices) {
    m_vertices = vertices;
}


const std::vector<TriangleFace>& Mesh::GetFaces() const {
    return m_faces;
}


void Mesh::SetFaces(const std::vector<TriangleFace>& faces) {
    m_faces = faces;
}
