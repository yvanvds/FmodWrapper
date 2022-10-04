#pragma once


#include <cstdlib>
#include <time.h> 
#include <cmath>
#include "defines.h"

namespace FW {
    template<typename T0, typename T1, typename T2>
    inline API void  Clamp(T0& x, T1  min, T2  max) { if (x < min)x = min; else if (x > max)x = max; }
    inline API void Randomize() { srand(static_cast<unsigned int>(::time(nullptr))); }
    inline API int Random(int max) { return rand() % max; }
    inline API int Random(int min, int max) { return min + (rand() % (max - min)); }
    inline API int BigRandom(int max) {
        max = static_cast<int>(sqrt(max));
        return ((rand() % max) * (rand() % max));
    }

    inline API float RandomF() { return (float)rand() / (float)RAND_MAX; }
    inline API float RandomF(float max) { return (float)rand() / (float)RAND_MAX * max; }
    inline API float RandomF(float min, float max) { return min + ((float)rand() / (float)RAND_MAX * (max - min)); }

    inline API float* Random(float* min, float* max) { return min + (rand() % (max - min)); }

    const float Pi_6 = 0.52359878f; // PI/6 ( 30 deg)
    const float Pi_4 = 0.78539816f; // PI/4 ( 45 deg)
    const float Pi_3 = 1.04719755f; // PI/3 ( 60 deg)
    const float Pi_2 = 1.57079633f; // PI/2 ( 90 deg)
    const float Pi = 3.14159265f; // PI   (180 deg)
    const float Pi2 = 6.28318531f; // PI*2 (360 deg)
    const float ToDegrees = 57.29577951f;
    const float ToRadians = 0.017453293f;

    const float Sqrt2 = 1.4142135623730950f; // Sqrt(2)
    const float Sqrt3 = 1.7320508075688773f; // Sqrt(3)
    const float Sqrt2_2 = 0.7071067811865475f; // Sqrt(2)/2
    const float Sqrt3_3 = 0.5773502691896257f; // Sqrt(3)/3
}