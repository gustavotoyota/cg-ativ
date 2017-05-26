attribute vec3 vert;
attribute vec2 uv;
attribute vec3 normal;

varying vec2 varUv;
varying vec3 varNormal;

uniform mat4 transform;

void main() {
    varUv = uv;
    varNormal = normal;
	
    gl_Position = transform * vec4(vert, 1.0);
}