varying vec2 varUv;
varying vec3 varNormal;

void main() {
    gl_FragColor = vec4((gl_FragCoord.z - 0.5f) * 2.0f);
}