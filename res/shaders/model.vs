attribute vec3 vert;
attribute vec2 uv;
attribute vec3 normal;

varying vec3 varPos;
varying vec2 varUv;
varying vec3 varNormal;

uniform mat3 model3;
uniform mat4 model4;
uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(vert, 1.0);
    
    varPos = vec3(model4 * vec4(vert, 1.0));
    varUv = uv;
    varNormal = normalize(model3 * normal);
}
