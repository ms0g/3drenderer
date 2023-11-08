#pragma once

namespace Mathf {
float Lerp(float a, float b, float t) {
    return a + t * (b - a);
}
}

