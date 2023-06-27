#pragma once

template <typename T>
T floor(const T& var) {
    if (var >= 0) {
        return static_cast<T>(static_cast<int>(var));
    }
    else {
        T intPart = static_cast<T>(static_cast<int>(var));
        return (intPart > var) ? intPart - static_cast<T>(1) : intPart;
    }
}


__forceinline float lerp(float a, float b, float t)
{
    return (1.0f - t) * a + t * b;
}