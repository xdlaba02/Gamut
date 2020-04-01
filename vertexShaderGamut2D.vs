#version 130
in vec3 position;
out vec3 pos;
uniform mat4 mvpMatrix;
void main() {
  vec3 xyz = vec3(position[0], position[1], 1 - position[0] - position[1]);
  gl_Position = mvpMatrix * vec4(xyz, 1.0);
  pos = position;
};
