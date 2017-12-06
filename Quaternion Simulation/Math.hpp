#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <iostream>

class Quaternion;

struct Vector
{
    double x,y,z;

    Vector() : x(0),y(0),z(0) {}
    Vector(double a, double b, double c) : x(a),y(b),z(c) {}

    double magnitude()
    {
        return std::sqrt(x*x+y*y+z*z);
    }
    double magnitudeSquared()
    {
        return x*x+y*y+z*z;
    }
    void normalize()
    {
        double m =sqrt(x*x + y*y + z*z);
        x = (x)/m;
        y = (y)/m;
        z = (z)/m;
    }

    double polarAngle()
    {
        return (90-acos(z)*180/3.14159265); //really needs to be a unit vector lol
    }
    double yaw()
    {
        if (z==1)
            return 0;
        return atan2(x,y)*180/3.14159265-90;
    }

    Vector crossProduct(const Vector& r)
    {
        Vector t;
        t.x = y*r.z - z*r.y;
        t.y = z*r.x - x*r.z;
        t.z = x*r.y - y*r.x;
        return t;
    }

    void operator= (const Quaternion& q);

    friend std::ostream& operator<< (std::ostream& os, const Vector& v)
    {
        os << "(" << v.x << "," << v.y << "," << v.z << ")";
        return os;
    }
};

struct Quaternion
{
    double a,b,c,d; //a + bi + cj + dk

    Quaternion() : a(0),b(0),c(0),d(0) {}
    Quaternion(double angle, Vector axis) //assume unit vector axis
    {
        double t = sin(angle/360*3.14159265);
        a = cos(angle/360*3.14159265);
        b = t*axis.x;
        c = t*axis.y;
        d = t*axis.z;
    }
    Quaternion(double r, double i, double j, double k)
    {
        a = r;
        b = i;
        c = j;
        d = k;
    }
    Quaternion(Vector vec)
    {
        a = 0;
        b = vec.x;
        c = vec.y;
        d = vec.z;
    }

    Quaternion operator* (const Quaternion& r)
    {
        Quaternion t;
        t.a = r.a*a - r.b*b - r.c*c - r.d*d;
        t.b = r.a*b + r.b*a - r.c*d + r.d*c;
        t.c = r.a*c + r.b*d + r.c*a - r.d*b;
        t.d = r.a*d - r.b*c + r.c*b + r.d*a;
        return t;
    }
    Quaternion operator* (const Vector& r)
    {
        Quaternion t;
        t.a = -r.x*b - r.y*c - r.z*d;
        t.b = r.x*a - r.y*d + r.z*c;
        t.c = r.x*d + r.y*a - r.z*b;
        t.d = -r.x*c + r.y*b + r.z*a;
        return t;
    }

    Quaternion reciporical()
    {
        return Quaternion(a,-b,-c,-d);
    }

    void rotatePoint(Vector& point)
    {
        point = (*this)*point*reciporical();
    }

    void normalize()
    {
        double m = a*a + b*b + c*c + d*d;
        a = a*a/m;
        b = b*b/m;
        c = c*c/m;
        d = d*d/m;
    }

    double magnitude()
    {
        return sqrt(a*a + b*b + c*c + d*d);
    }
    double magnitudeSquared()
    {
        return a*a + b*b + c*c + d*d;
    }
};

inline void Vector::operator= (const Quaternion& q)
{
    x = q.b;
    y = q.c;
    z = q.d;
}


#endif // MATH_HPP
