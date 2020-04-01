#version 130
in vec3 pos;
out vec4 fragColor;

uniform mat3 colorMatrix;
uniform float gamma;

vec3 pow_vec3(vec3 v, float val) {
  return vec3(pow(v[0], val), pow(v[1], val), pow(v[2], val));
}

void main() {
  vec3 XYZ = vec3(pos[2] * pos[0] / pos[1], pos[2], pos[2] * (1.f - pos[0] - pos[1]) / pos[1]);
  vec3 RGB = pow_vec3(clamp(colorMatrix * XYZ, 0, 1), 1.f / gamma);
  fragColor = vec4(RGB, 1.0);
}
