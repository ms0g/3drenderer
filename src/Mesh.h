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

    void SetRotation(const Vec3& mRotation);

    [[nodiscard]] const Vec3& GetScale() const;

    void SetScale(const Vec3& mScale);

    [[nodiscard]] const Vec3& GetTranslation() const;

    void SetTranslation(const Vec3& mTranslation);

    [[nodiscard]] const std::vector<Vec3>& GetVertices() const;

    void SetVertices(const std::vector<Vec3>& mVertices);

    [[nodiscard]] const std::vector<TriangleFace>& GetFaces() const;

    void SetFaces(const std::vector<TriangleFace>& mFaces);

    uint32_t* texture{};

private:
    Vec3 m_rotation;
    Vec3 m_scale;
    Vec3 m_translation;
    std::vector<Vec3> m_vertices;
    std::vector<TriangleFace> m_faces;
};





