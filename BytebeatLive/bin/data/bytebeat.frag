#extension GL_EXT_gpu_shader4 : enable
const int width = 1280*800;
void main() {
  int t = int(gl_FragCoord.y) * width + int(gl_FragCoord.x);
  int v =

    (t*7&t>>2)|(t*11&t>>11);

  gl_FragColor = vec4(vec3(float(v % 256) / 256.),1.);
}
