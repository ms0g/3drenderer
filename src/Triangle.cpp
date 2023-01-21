#include "Triangle.h"
#include <utility>
#include "Graphics.h"

///////////////////////////////////////////////////////////////////////////////
// Draw a filled triangle with the flat-top/flat-bottom method
// We split the original triangle in two, half flat-bottom and half flat-top
///////////////////////////////////////////////////////////////////////////////
//
//          (x0,y0)
//            / \
//           /   \
//          /     \
//         /       \
//        /         \
//   (x1,y1)------(Mx,My)
//       \_           \
//          \_         \
//             \_       \
//                \_     \
//                   \    \
//                     \_  \
//                        \_\
//                           \
//                         (x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
void Triangle::FillWithColor(Graphics& graphics, color_t color) {
    int x0 = points[0].x;
    int y0 = points[0].y;

    int x1 = points[1].x;
    int y1 = points[1].y;

    int x2 = points[2].x;
    int y2 = points[2].y;

    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }

    if (y1 > y2) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }

    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }

    if (y1 == y2) {
        // Draw flat-bottom triangle
        graphics.FillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        // Draw flat-top triangle
        graphics.FillFlatTopTriangle(x0, y0, x1, y1, x2, y2, color);
    } else {
        // Calculate the new vertex (Mx,My) using triangle similarity
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        // Draw flat-bottom triangle
        graphics.FillFlatBottomTriangle(x0, y0, x1, y1, Mx, My, color);

        // Draw flat-top triangle
        graphics.FillFlatTopTriangle(x1, y1, Mx, My, x2, y2, color);
    }

}