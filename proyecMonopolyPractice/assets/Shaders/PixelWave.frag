uniform sampler2D texture;
uniform float time;
uniform float waveIntensity;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    uv.y += sin(uv.x * 10.0 + time * waveIntensity) * 0.05;
    gl_FragColor = texture2D(texture, uv);
}
