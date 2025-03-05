#pragma once

#include "utils/glm_utils.h"


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        return glm::mat3(1, 0, 0,
                        0, 1, 0,
                        translateX, translateY, 1);
    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        return glm::mat3(scaleX, 0, 0,
                         0, scaleY, 0,
                         0, 0, 1);

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        float cosx = cos(radians);
        float sinx = sin(radians);

        return glm::mat3(cosx, sinx, 0,
            -sinx, cosx, 0,
            0, 0, 1);
    }

    inline glm::mat3 Forfecare(float x)
    {
        return glm::mat3(1, x, 0,
                        0, 1, 0,
                        0, 0, 1);

    }

}   

// namespace transform2D
