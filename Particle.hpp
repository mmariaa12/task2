#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>

#include "Vector3d.hpp"

class Particle {
public:
    Particle(void);
    Particle(Vector3d x, Vector3d v, double m, double q, double t);
    Particle(const Particle &p);

    Particle &operator=(const Particle &p);

    static Vector3d force(const Particle &dest, const Particle &src);
    static bool detect_collision(const Particle &p1, const Particle &p2,
                                 double l);

    Particle &collide_in_place(const Particle &p);

    Particle &set_force(const Vector3d &f);
    Particle &update_in_place(double dt);

private:
    Vector3d x, v, f;
    double m, q, t;

    friend std::ostream &operator<<(std::ostream &os, const Particle &p);

    friend bool operator==(const Particle &p1, const Particle &p2);
    friend bool operator!=(const Particle &p1, const Particle &p2);
};

#endif
