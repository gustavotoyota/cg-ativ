varying vec2 varUv;
varying vec3 varNormal;

uniform sampler2D tex;

void main() {
    gl_FragColor = texture2D(tex, vec2(1, -1) * varUv);
}
