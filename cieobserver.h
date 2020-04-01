#ifndef CIEOBSERVER_H
#define CIEOBSERVER_H

template <typename F>
float getFunctionValue(float start, float step, F &&function, int N, float x) {
  int   i     = static_cast<int>(x - start) / step;
  float delta = (x - (i * step + start)) / step;

  if (i < N - 1) {
    return function(i) + delta * (function(i + 1) - function(i));;
  }
  else if (i < N) {
    return function(i);
  }
  else {
    return 0;
  }
}

void getCIEXYZ(float lambda, int observer, float &x, float &y, float &z);
float getIlluminant(float lambda, int illuminant);
void CIEXYZfromSurfaceReflectance(float lambda_min, int N, float step, float reflectance[], float &X, float &Y, float &Z, int illuminant, int observer);

#endif // CIEOBSERVER_H
