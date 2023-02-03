#include "ObjParser.h"
#include <fstream>
#include "Vec3.h"
#include "MeshData.hpp"

MeshData ObjParser::Load(const std::string& fileName) {
    MeshData data;
    std::ifstream file;

    file.open(fileName.c_str());
    if (!file.is_open()) return {};

    std::string line;

    while (std::getline(file, line)) {
        // Vertex information
        if (strncmp(line.c_str(), "v ", 2) == 0) {
            Vec3 vertex;
            sscanf(line.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            data.vertices.push_back(vertex);
        }
        // Face information
        if (strncmp(line.c_str(), "f ", 2) == 0) {
            int vertex_indices[3];
            int texture_indices[3];
            int normal_indices[3];
            sscanf(
                    line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                    &vertex_indices[0], &texture_indices[0], &normal_indices[0],
                    &vertex_indices[1], &texture_indices[1], &normal_indices[1],
                    &vertex_indices[2], &texture_indices[2], &normal_indices[2]
            );
            TriangleFace face = {
                    vertex_indices[0],
                    vertex_indices[1],
                    vertex_indices[2],
                    0xFFFFFFFF
            };
            data.faces.push_back(face);
        }
    }
    file.close();
    return data;
}
