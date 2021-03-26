#include "Vector3d.hpp"

#include <cassert>
#include <cmath>

#ifndef EPS
#define EPS 1e-9
#endif

Vector3d::Vector3d(void) {
    for (int i = 0; i < 3; ++i) {
        (*this)[i] = 0;
    }
}

Vector3d::Vector3d(double x, double y, double z) {
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
}

Vector3d::Vector3d(const Vector3d &v) {
    for (int i = 0; i < 3; ++i) {
        (*this)[i] = v[i];
    }
}

double &Vector3d::operator[](int i) {
    assert(0 <= i && i < 3);

    return this->x[i];
}

double Vector3d::operator[](int i) const {
    assert(0 <= i && i < 3);

    return this->x[i];
}

Vector3d &Vector3d::operator=(const Vector3d &v) {
    for (int i = 0; i < 3; ++i) {
        (*this)[i] = v[i];
    }

    return *this;
}

Vector3d &Vector3d::operator+=(const Vector3d &v) {
    for (int i = 0; i < 3; ++i) {
        (*this)[i] += v[i];
    }

    return *this;
}

Vector3d &Vector3d::operator-=(const Vector3d &v) {
    for (int i = 0; i < 3; ++i) {
        (*this)[i] -= v[i];
    }

    return *this;
}

Vector3d &Vector3d::operator*=(double k) {
    for (int i = 0; i < 3; ++i) {
        (*this)[i] *= k;
    }

    return *this;
}

Vector3d &Vector3d::operator/=(double k) {
    assert(fabs(k) >= EPS);

    for (int i = 0; i < 3; ++i) {
        (*this)[i] /= k;
    }

    return *this;
}

double Vector3d::square(void) const { return dot_product(*this, *this); }

double Vector3d::norm(void) const { return sqrt(this->square()); }

Vector3d &Vector3d::normalize_in_place(void) { return *this /= this->norm(); }
Vector3d Vector3d::normalize(void) const { return *this / this->norm(); }

std::ostream &operator<<(std::ostream &os, const Vector3d &v) {
    return os << "[" << v[0] << ", " << v[1] << ", " << v[2] << "]";
}

Vector3d operator+(const Vector3d &v, const Vector3d &u) {
    Vector3d out;

    for (int i = 0; i < 3; ++i) {
        out[i] = v[i] + u[i];
    }

    return out;
}

Vector3d operator-(const Vector3d &v, const Vector3d &u) {
    Vector3d out;

    for (int i = 0; i < 3; ++i) {
        out[i] = v[i] - u[i];
    }

    return out;
}

Vector3d operator*(double k, const Vector3d &v) {
    Vector3d out;

    for (int i = 0; i < 3; ++i) {
        out[i] = k * v[i];
    }

    return out;
}

Vector3d operator*(const Vector3d &v, double k) { return k * v; }

Vector3d operator/(const Vector3d &v, double k) {
    Vector3d out;

    assert(fabs(k) >= EPS);

    for (int i = 0; i < 3; ++i) {
        out[i] = v[i] / k;
    }

    return out;
}

double dot_product(const Vector3d &v, const Vector3d &u) {
    double sum = 0;

    for (int i = 0; i < 3; ++i) {
        sum += v[i] * u[i];
    }
    return sum;
}

bool operator==(const Vector3d &v, const Vector3d &u) {
    return (v - u).square() < EPS;
}

bool operator!=(const Vector3d &v, const Vector3d &u) { return !(v == u); }
