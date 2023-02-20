#pragma once

#include <vector>
#include <string>


class vec3;
class MeshData;
class TriangleFace;
namespace ObjParser {
MeshData Load(const std::string& fileName);
}
