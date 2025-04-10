uniform sampler2D texture;
uniform vec2 resolution;
uniform float time;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution;

    // Efecto de onda basado en el tiempo
    uv.y += sin(uv.x * 10.0 + time * 5.0) * 0.05;
    uv.x += cos(uv.y * 10.0 + time * 5.0) * 0.05;

    gl_FragColor = texture2D(texture, uv);
}
