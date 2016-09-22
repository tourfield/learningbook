#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double mysqrt(double d) {
#if defined(HAVE_LOG) && defined(HAVE_EXP)
  return sqrt(d);
#else
  return exp(log(d) * 0.5);
#endif
}
