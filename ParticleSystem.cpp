#include <cassert>
#include <cmath>

#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(size_t n) {
    assert(n > 0);

    this->ps = new Particle *[n];

    for (size_t i = 0; i < n; ++i) {
        this->ps[i] = new Particle;
    }

    this->n = n;
}

ParticleSystem::~ParticleSystem(void) {
    for (size_t i = 0; i < this->n; ++i) {
        delete this->ps[i];
    }

    delete[] this->ps;
}

Particle &ParticleSystem::operator[](size_t i) {
    assert(i < this->n);

    return *this->ps[i];
}

const Particle &ParticleSystem::operator[](size_t i) const {
    assert(i < this->n);

    return *this->ps[i];
}

size_t ParticleSystem::get_n(void) const { return this->n; }

ParticleSystem &ParticleSystem::set_forces(void) {
    Vector3d total_force;

    for (size_t i = 0; i < this->n; ++i) {
        total_force = Vector3d();
        for (size_t j = 0; j < this->n; ++j) {
            if (i != j) {
                total_force += Particle::force(*this->ps[i], *this->ps[j]);
            }
        }

        this->ps[i]->set_force(total_force);
    }

    return *this;
}

ParticleSystem &ParticleSystem::update(double dt) {
    for (size_t i = 0; i < this->n; ++i) {
        this->ps[i]->update_in_place(dt);
    }

    return *this;
}

ParticleSystem &ParticleSystem::detect_and_collide(double l) {
    for (size_t i = 0; i < this->n; ++i) {
        for (size_t j = 0; j < this->n; ++j) {
            if (i != j &&
                Particle::detect_collision(*this->ps[i], *this->ps[j], l)) {
                this->ps[i]->collide_in_place(*this->ps[j]);

                delete this->ps[j];
                this->ps[j] = this->ps[n - 1];

                i = 0;
                --this->n;
                break;
            }
        }
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const ParticleSystem &ps) {
    Vector3d avg_x, avg_v;
    double avg_m = 0, avg_q = 0, avg_t = 0;
    double Dx = 0, Dv = 0, Dm = 0, Dq = 0, Dt = 0;

    for (size_t i = 0; i < ps.n; ++i) {
        avg_x += ps[i].x;
        avg_v += ps[i].v;
        avg_m += ps[i].m;
        avg_q += ps[i].q;
        avg_t += ps[i].t;
    }

    avg_x /= ps.n;
    avg_v /= ps.n;
    avg_m /= ps.n;
    avg_q /= ps.n;
    avg_t /= ps.n;

    for (size_t i = 0; i < ps.n; ++i) {
        Dx += (ps[i].x - avg_x).square();
        Dv += (ps[i].v - avg_v).square();
        Dm += fabs(ps[i].m - avg_m);
        Dq += fabs(ps[i].q - avg_q);
        Dt += fabs(ps[i].t - avg_t);
    }

    Dx /= ps.n;
    Dv /= ps.n;
    Dm /= ps.n;
    Dq /= ps.n;
    Dt /= ps.n;

    return os << "<ParticleSystem: \navg: {\n x: " << avg_x
              << ",\n v: " << avg_v << ",\n m: " << avg_m << ",\n q: " << avg_q
              << ",\n t: " << avg_t << "\n},\nD: {\n x: " << Dx
              << ",\n v: " << Dv << ",\n m: " << Dm << ",\n q: " << Dq
              << ",\n t: " << Dt << "\n}>";
}
