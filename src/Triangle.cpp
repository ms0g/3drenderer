#include "Triangle.h"
#include "Vec3.h"

vec3 ComputeTriangleNormal(vec4* vertices) {
    vec3 vecA = vec3::FromVec4(vertices[0]);     /*    A    */
    vec3 vecB = vec3::FromVec4(vertices[1]);     /*  /   \  */
    vec3 vecC = vec3::FromVec4(vertices[2]);     /* C-----B */

    // Get the vector subtraction of B-A and C-A
    vec3 ab = vecB - vecA;
    vec3 ac = vecC - vecA;
    ab.Normalize();
    ac.Normalize();

    // Compute the face normal
    vec3 normal = ab.Cross(ac);
    normal.Normalize();

    return normal;
}
