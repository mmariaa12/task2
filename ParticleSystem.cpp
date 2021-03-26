#include <cassert>

#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(size_t n) {
    assert(n > 0);

    this->ps = new Particle *[n];

    for (size_t i = 0; i < n; ++i) {
        this->ps[i] = NULL;
    }

    this->n = n;
}

ParticleSystem::~ParticleSystem(void) {
    for (size_t i = 0; i < this->n; ++i) {
        if (this->ps[i] != NULL) {
            delete this->ps[i];
        }
    }

    delete[] this->ps;
}

ParticleSystem &ParticleSystem::particle_realloc(size_t i) {
    assert(i < this->n);

    if (this->ps[i] != NULL) {
        delete this->ps[i];
    }

    this->ps[i] = new Particle;

    return *this;
}

ParticleSystem &ParticleSystem::particle_realloc(size_t i, Vector3d x,
                                                 Vector3d v, double m, double q,
                                                 double t) {
    assert(i < this->n);

    if (this->ps[i] != NULL) {
        delete this->ps[i];
    }

    this->ps[i] = new Particle(x, v, m, q, t);

    return *this;
}

ParticleSystem &ParticleSystem::particle_realloc(size_t i, const Particle &p) {
    assert(i < this->n);

    if (this->ps[i] != NULL) {
        delete this->ps[i];
    }

    this->ps[i] = new Particle(p);

    return *this;
}

Particle &ParticleSystem::operator[](size_t i) {
    assert(i < this->n);
    assert(this->ps[i] != NULL);

    return *this->ps[i];
}

const Particle &ParticleSystem::operator[](size_t i) const {
    assert(i < this->n);
    assert(this->ps[i] != NULL);

    return *this->ps[i];
}
