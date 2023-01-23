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

    [[nodiscard]] std::vector<TriangleFace>& GetFaces();

    [[nodiscard]] std::vector<Vec3>& GetVertices();

    [[nodiscard]] float GetRotationX() const;

    [[nodiscard]] float GetRotationY() const;

    [[nodiscard]] float GetRotationZ() const;


private:
    Vec3 m_rotation;
    std::vector<Vec3> m_vertices;
    std::vector<TriangleFace> m_faces;
};





