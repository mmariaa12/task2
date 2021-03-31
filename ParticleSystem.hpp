#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <iostream>

#include "Particle.hpp"

class ParticleSystem {
public:
    ParticleSystem(size_t n);
    ~ParticleSystem(void);

    Particle &operator[](size_t i);
    const Particle &operator[](size_t i) const;

    size_t get_n(void) const;

    ParticleSystem &detect_and_collide(double l);
    ParticleSystem &set_forces(void);
    ParticleSystem &update(double dt);

private:
    Particle **ps;
    size_t n;

    friend std::ostream &operator<<(std::ostream &os, const ParticleSystem &ps);
};

#endif
