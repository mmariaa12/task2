#include <cmath>
#include <iostream>

#include "ParticleSystem.hpp"

#define KCOULOMB 8.9e+9
#define KGRAVITATIONAL 6.6e-11

bool test1(void) {

    Particle p1;
    Particle p2;

    p1 = Particle(Vector3d(1, 0, 0), Vector3d(0, 0, 0), 1 / KGRAVITATIONAL, 1,
                  0);

    p2 = Particle(Vector3d(0, 0, 0), Vector3d(0, 0, 0), 1, 1 / KCOULOMB, 0);

    if (Particle::force(p1, p2) != Vector3d(2, 0, 0)) {
        return false;
    }

    if (Particle::detect_collision(p1, p2, 1 / 2) != false ||
        Particle::detect_collision(p1, p2, 1) != false ||
        Particle::detect_collision(p1, p2, 2) != true) {
        return false;
    }

    return true;
}

bool test2(void) {
    Particle ps[10];
    double pi = acos(-1);
    double angle;

    for (int i = 0; i < 10; ++i) {
        angle = 2 * pi * i / 10;
        ps[i] = Particle(Vector3d(cos(angle), sin(angle), 0), Vector3d(1, 1, 1),
                         1, 1, 1);
    }

    for (int i = 1; i < 10; ++i) {
        ps[0].collide_in_place(ps[i]);
    }

    if (ps[0] != Particle(Vector3d(0, 0, 0), Vector3d(0, 0, 0), 10, 10, 1)) {
        return false;
    }

    return true;
}

bool test3(void) {
    ParticleSystem ps(10);

    ps.particle_realloc(1, Vector3d(1, 1, 1), Vector3d(2, 2, 2), 3, 4, 5);
    ps[1].set_force(Vector3d(6, 6, 6));

    std::cout << ps[1] << std::endl;

    ps.particle_realloc(1);
    std::cout << ps[1] << std::endl;

    return true;
}

int main(void) { std::cout << test3() << std::endl; }
