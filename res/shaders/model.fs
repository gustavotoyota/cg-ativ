varying vec3 varPos;
varying vec2 varUv;
varying vec3 varNormal;

uniform sampler2D tex;

uniform float fade;
uniform vec3 lightPos;

void main() {
    float light = dot(varNormal, normalize(lightPos - varPos)) / 2.0 + 0.5;

    gl_FragColor = texture2D(tex, vec2(1, -1) * varUv) * vec4(vec3(light * fade), 1);
}
