#pragma once

#include <vector>
#include <string>

class Vec3;
class MeshData;
class TriangleFace;

namespace ObjParser {

MeshData Load(const std::string& fileName);
}
