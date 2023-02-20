#include "Mesh.h"
#include "MeshData.hpp"
#include "ObjParser.h"


Mesh::Mesh(const char* objFile, const char* textureFile, vec3 scale, vec3 translation, vec3 rotation) :
        m_scale(scale),
        m_translation(translation),
        m_rotation(rotation) {
    auto meshData = ObjParser::Load(objFile);

    // Fill vertices
    m_vertices = meshData.vertices;

    // Fill faces
    m_faces = meshData.faces;

    m_texture = std::make_unique<Texture>(textureFile);
}


const Texture& Mesh::GetTexture() const {
    return *m_texture;
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
