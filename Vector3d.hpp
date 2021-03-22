#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <iostream>

class Vector3d {
public:
    Vector3d(void);
    Vector3d(double x, double y, double z);
    Vector3d(const Vector3d &v);

    double &operator[](int i);
    double operator[](int i) const;

    Vector3d &operator=(const Vector3d &v);

    Vector3d &operator+=(const Vector3d &v);
    Vector3d &operator-=(const Vector3d &v);

    Vector3d &operator*=(double k);
    Vector3d &operator/=(double k);

    double square(void) const;
    double norm(void) const;
    Vector3d &normalize_in_place(void);
    Vector3d normalize(void) const;

private:
    double x[3];

    friend std::ostream &operator<<(std::ostream &os, const Vector3d &v);

    friend Vector3d operator+(const Vector3d &v, const Vector3d &u);
    friend Vector3d operator-(const Vector3d &v, const Vector3d &u);

    friend Vector3d operator*(double k, const Vector3d &v);
    friend Vector3d operator*(const Vector3d &v, double k);
    friend Vector3d operator/(const Vector3d &v, double k);

    friend double dot_product(const Vector3d &v, const Vector3d &u);
};

#endif