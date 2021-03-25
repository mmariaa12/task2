#include "Particle.hpp"

#define KGRAVITATIONAL 6.6e-11
#define KCOULOMB 8.9e+9

Particle::Particle(void) : x(), v(), f(), m(0), q(0), t(0) {}

Particle::Particle(Vector3d x, Vector3d v, Vector3d f, double m, double q,
                   double t)
    : x(x), v(v), f(f), m(m), q(q), t(t) {}

Particle::Particle(const Particle &p)
    : x(p.x), v(p.v), f(p.f), m(p.m), q(p.q), t(p.t) {}

Particle &Particle::operator=(const Particle &p) {
    this->x = p.x;
    this->v = p.v;
    this->f = p.f;
    this->m = p.m;
    this->q = p.q;
    this->t = p.t;

    return *this;
}

Vector3d Particle::force(const Particle &dest, const Particle &src) {
    double gravitational_magnitude, coulomb_magnitude;
    double direction_square;
    Vector3d direction;

    direction = dest.x - src.x;
    direction_square = direction.square();

    gravitational_magnitude =
        KGRAVITATIONAL * dest.m * src.m / direction_square;
    coulomb_magnitude = KCOULOMB * dest.q * src.q / direction_square;

    return (gravitational_magnitude + coulomb_magnitude) *
           direction.normalize();
}

bool Particle::detect_collision(const Particle &p1, const Particle &p2,
                                double l) {
    return (p1.x - p2.x).square() < l * l;
}

Particle &Particle::collide_in_place(const Particle &p) {
    double m, this_v_square;

    this->x = (this->x + p.x) / 2;
    this->q += p.q;

    m = this->m + p.m;
    this_v_square = this->v.square();

    this->v = (this->m * this->v + p.m * p.v) / m;

    this->t = (this->m * (this->t + this_v_square / 2) +
               p.m * (p.t + p.v.square() / 2)) /
                  m -
              this->v.square();
    this->m = m;

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Particle &p) {
    return os << "{\n x: " << p.x << ",\n v: " << p.v << ",\n f: " << p.f
              << ",\n m: " << p.m << ",\n q: " << p.q << ",\n t: " << p.t
              << "\n}";
}