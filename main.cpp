#include <cmath>
#include <iostream>

#include "Particle.hpp"

#define KCOULOMB 8.9e+9
#define KGRAVITATIONAL 6.6e-11

int main(void) {
    {
        Particle p1;
        Particle p2;

        p1 = Particle(Vector3d(1, 0, 0), Vector3d(0, 0, 0), Vector3d(0, 0, 0),
                      1 / KGRAVITATIONAL, 1, 0);

        p2 = Particle(Vector3d(0, 0, 0), Vector3d(0, 0, 0), Vector3d(0, 0, 0),
                      1, 1 / KCOULOMB, 0);

        std::cout << p1 << '\n'
                  << p2 << '\n'
                  << Particle::force(p1, p2) << std::endl;

        std::cout << Particle::detect_collision(p1, p2, 1 / 2) << '\n'
                  << Particle::detect_collision(p1, p2, 1) << '\n'
                  << Particle::detect_collision(p1, p2, 2) << std::endl;
    }

    {
        Particle *pss = new Particle[10];
        double pi = acos(-1);
        double angle;

        for (int i = 0; i < 10; ++i) {
            angle = 2 * pi * i / 10;
            pss[i] = Particle(Vector3d(cos(angle), sin(angle), 0),
                              Vector3d(0, 0, 0), Vector3d(0, 0, 0), 1, 1, 1);
            std::cout << pss[i] << std::endl;
        }

        for (int i = 1; i < 10; ++i) {
            pss[0].collide_in_place(pss[i]);
        }

        std::cout << pss[0] << std::endl;
    }
}
