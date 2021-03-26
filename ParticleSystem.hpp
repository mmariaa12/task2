#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <iostream>

#include "Particle.hpp"

class ParticleSystem {
public:
    ParticleSystem(size_t n);
    ~ParticleSystem(void);

    ParticleSystem &particle_realloc(size_t i);
    ParticleSystem &particle_realloc(size_t i, Vector3d x, Vector3d v, double m,
                                     double q, double t);
    ParticleSystem &particle_realloc(size_t i, const Particle &p);

    Particle &operator[](size_t i);
    const Particle &operator[](size_t i) const;

private:
    Particle **ps;
    size_t n;
};

#endif
