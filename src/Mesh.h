#pragma once

#include <vector>
#include "Vec3.h"
#include "Triangle.h"


class Mesh {
public:
    Mesh() = default;

    void SetData(std::vector<Vec3>& vertices, std::vector<TriangleFace>& faces);

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





