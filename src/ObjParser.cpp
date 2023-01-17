#include "ObjParser.h"
#include "Vec3.h"
#include "Triangle.h"
#include "MeshData.hpp"

MeshData ObjParser::Load(const std::string& fileName) {
    MeshData data;
    FILE* file;
    file = fopen(fileName.c_str(), "r");
    char line[1024];

    while (fgets(line, 1024, file)) {
        // Vertex information
        if (strncmp(line, "v ", 2) == 0) {
            Vec3 vertex;
            sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            data.vertices.emplace_back(vertex);
        }
        // Face information
        if (strncmp(line, "f ", 2) == 0) {
            int vertex_indices[3];
            int texture_indices[3];
            int normal_indices[3];
            sscanf(
                    line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                    &vertex_indices[0], &texture_indices[0], &normal_indices[0],
                    &vertex_indices[1], &texture_indices[1], &normal_indices[1],
                    &vertex_indices[2], &texture_indices[2], &normal_indices[2]
            );
            TriangleFace face = {
                    vertex_indices[0],
                    vertex_indices[1],
                    vertex_indices[2]
            };
            data.faces.emplace_back(face);
        }
    }
    return data;
}