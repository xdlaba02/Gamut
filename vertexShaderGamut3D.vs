#version 130
in vec3 position;
out vec3 pos;
uniform mat4 mvpMatrix;
uniform float pointSize;
void main() {
  gl_PointSize = pointSize;
  gl_Position = mvpMatrix * vec4(position, 1.0);
  pos = position;
};
