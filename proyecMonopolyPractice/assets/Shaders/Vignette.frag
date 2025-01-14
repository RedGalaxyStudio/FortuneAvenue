uniform sampler2D texture;
uniform vec2 center;  // Centro del viñeteado
uniform float radius; // Radio del viñeteado

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    float dist = distance(uv, center);
    float vignette = smoothstep(radius, radius - 0.1, dist);
    vec4 texColor = texture2D(texture, uv);
    gl_FragColor = vec4(texColor.rgb * vignette, texColor.a);
}
