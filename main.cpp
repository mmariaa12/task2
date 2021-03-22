#include <iostream>

#include "Vector3d.hpp"

int main(void) {
    Vector3d v(1, 2, 3);

    Vector3d x;

    std::cout << x << std::endl;
    x += v;
    std::cout << x << std::endl;
    x *= 3;
    std::cout << x << std::endl;

    Vector3d y;

    y = x + v;
    std::cout << y << std::endl;

    y = 5 * x;
    std::cout << y << std::endl;
    y = x * 7;
    std::cout << y << std::endl;

    Vector3d z(1, 1, 0);

    z.normalize_in_place();
    std::cout << z << std::endl;
}
