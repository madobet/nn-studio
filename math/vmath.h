#ifndef VMATH_H
#define VMATH_H
#include <math.h>

const double eps = 0.004;

// some simple math functions
inline int MyAbs(int x) { return (x<0)?(-x):x;}
inline double MyAbs(double x) { return (x<0)?(-x):x; }
inline int MyMin(int x, int y) { return (x<y)?x:y; }
inline double MyMin(double x, double y) { return (x<y)?x:y; }
inline int Sgn(int x) { return (x>0)?1:( (x<0)?(-1):0 ); }
inline double Sgn(double x) { return (x>0)?1:( (x<0)?(-1):0 ); }
inline double Sigmoid(double x) { return 1/(1 + exp(-x/eps)); }
double RKMethod();  // 4th R-K Method

#endif // VMATH_H
