#ifndef MATH_HPP
#define MATH_HPP

extern double _sinLookup[360];

double Sin(int angle);
double Cos(int angle);
double Tan(int angle);

void MatrixMultiply(double a[3][3], double b[3][3], double res[3][3]);
double DotProduct(double a[3], double b[3]);
void CrossProduct(double a[3], double b[3], double res[3]);
void vScale(double scalar, double vec[3], double res[3]);
void vAdd(double a[3], double b[3], double res[3]);

template <typename T>
bool withinThreshhold(T thresh, T val, T tolerance)
{
    return (thresh+tolerance>val && thresh-tolerance<val);
}

#endif // MATH_HPP
