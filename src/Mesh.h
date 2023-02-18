#pragma once

#include <vector>
#include "Vec3.h"
#include "Triangle.hpp"

class MeshData;
class PngTexture;
class Mesh {
public:
    Mesh() = default;

    void SetData(MeshData& meshData);

    [[nodiscard]] const PngTexture& GetTexture() const;

    void SetTexture(std::unique_ptr<PngTexture>& tex);

    [[nodiscard]] const vec3& GetRotation() const;

    void SetRotation(const vec3& rotation);

    void UpdateRotation(const vec3& rotation);

    [[nodiscard]] const vec3& GetScale() const;

    void SetScale(const vec3& scale);

    void UpdateScale(const vec3& scale);

    [[nodiscard]] const vec3& GetTranslation() const;

    void SetTranslation(const vec3& translation);

    void UpdateTranslation(const vec3& translation);

    [[nodiscard]] const std::vector<vec3>& GetVertices() const;

    void SetVertices(const std::vector<vec3>& vertices);

    [[nodiscard]] const std::vector<TriangleFace>& GetFaces() const;

    void SetFaces(const std::vector<TriangleFace>& faces);

private:
    vec3 m_rotation;
    vec3 m_scale;
    vec3 m_translation;
    std::vector<vec3> m_vertices;
    std::vector<TriangleFace> m_faces;
    std::unique_ptr<PngTexture> m_texture;
};





