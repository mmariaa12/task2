#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
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
    ParticleSystem ps(10);
    double pi = acos(-1), angle;

    for (int i = 0; i < 10; ++i) {
        angle = 2 * pi * i / 10;
        ps[i] = Particle(Vector3d(cos(angle), sin(angle), 0), Vector3d(1, 1, 1),
                         1, 1, 1);
    }

    ps.detect_and_collide(2);

    if (ps.get_n() != 1) {
        return false;
    }

    if (ps[0] != Particle(Vector3d(0, 0, 0), Vector3d(1, 1, 1), 10, 10, 1)) {
        return false;
    }

    return true;
}

void generate_random_system(ParticleSystem &ps) {
    for (size_t i = 0; i < ps.get_n(); ++i) {
        Vector3d x(rand() % 100, rand() % 100, rand() % 100);
        Vector3d v(rand() % 100, rand() % 100, rand() % 100);
        double m = rand() % 100 + 1;
        double q = rand() % 100 + 1;
        double t = rand() % 100 + 1;
        ps[i] = Particle(x, v, m, q, t);
    }
}

int main(int argc, char **argv) {
    assert(test1() && test2());

    if (argc < 5) {
        std::cerr << "Bad args" << std::endl;
        std::cerr << "Usage:\n" << argv[0] << " dt l n k" << std::endl;
        exit(EXIT_FAILURE);
    }

    double dt, l;
    int n, k;

    dt = atof(argv[1]);
    l = atof(argv[2]);
    n = atoi(argv[3]);
    k = atoi(argv[4]);

    ParticleSystem ps(n);

    srand(time(NULL));
    generate_random_system(ps);

    for (int i = 0; i < k; ++i) {
        std::cout << "Time passed: " << i * dt << std::endl;
        std::cout << "System: " << ps << std::endl;

        ps.detect_and_collide(l);
        ps.set_forces();
        ps.update(dt);
    }

    std::cout << "Time passed: " << k * dt << std::endl;
    std::cout << "System: " << ps << std::endl;
}
