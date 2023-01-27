#pragma once

#include <vector>
#include "Vec3.h"
#include "Triangle.hpp"

class MeshData;
class Mesh {
public:
    Mesh() = default;

    void SetData(MeshData& meshData);

    void UpdateRotation(float angle);

    void UpdateRotationX(float angle);

    void UpdateRotationY(float angle);

    void UpdateRotationZ(float angle);

    [[nodiscard]] float GetRotationX() const;

    [[nodiscard]] float GetRotationY() const;

    [[nodiscard]] float GetRotationZ() const;

    void SetRotationX(float angle);

    void SetRotationY(float angle);

    void SetRotationZ(float angle);

    void UpdateScale(float scalar);

    void UpdateScaleX(float scalar);

    void UpdateScaleY(float scalar);

    void UpdateScaleZ(float scalar);

    [[nodiscard]] float GetScaleX() const;

    [[nodiscard]] float GetScaleY() const;

    [[nodiscard]] float GetScaleZ() const;

    void SetScaleX(float scalar);

    void SetScaleY(float scalar);

    void SetScaleZ(float scalar);

    void UpdateTranslation(float coord);

    void UpdateTranslationX(float coord);

    void UpdateTranslationY(float coord);

    void UpdateTranslationZ(float coord);

    [[nodiscard]] float GetTranslationX() const;

    [[nodiscard]] float GetTranslationY() const;

    [[nodiscard]] float GetTranslationZ() const;

    void SetTranslationX(float coord);

    void SetTranslationY(float coord);

    void SetTranslationZ(float coord);

    [[nodiscard]] std::vector<TriangleFace>& GetFaces();

    [[nodiscard]] std::vector<Vec3>& GetVertices();

private:
    Vec3 m_rotation;
    Vec3 m_scale;
    Vec3 m_translation;
    std::vector<Vec3> m_vertices;
    std::vector<TriangleFace> m_faces;
};





