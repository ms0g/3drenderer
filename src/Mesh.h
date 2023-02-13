#pragma once

#include <vector>
#include "Vec3.h"
#include "Triangle.hpp"

class MeshData;

class Mesh {
public:
    Mesh() = default;

    void SetData(MeshData& meshData);

    [[nodiscard]] const Vec3& GetRotation() const;

    void SetRotation(const Vec3& rotation);

    void UpdateRotation(const Vec3& rotation);

    [[nodiscard]] const Vec3& GetScale() const;

    void SetScale(const Vec3& scale);

    void UpdateScale(const Vec3& scale);

    [[nodiscard]] const Vec3& GetTranslation() const;

    void SetTranslation(const Vec3& translation);

    void UpdateTranslation(const Vec3& translation);

    [[nodiscard]] const std::vector<Vec3>& GetVertices() const;

    void SetVertices(const std::vector<Vec3>& vertices);

    [[nodiscard]] const std::vector<TriangleFace>& GetFaces() const;

    void SetFaces(const std::vector<TriangleFace>& faces);

    uint32_t* texture{};

private:
    Vec3 m_rotation;
    Vec3 m_scale;
    Vec3 m_translation;
    std::vector<Vec3> m_vertices;
    std::vector<TriangleFace> m_faces;
};





