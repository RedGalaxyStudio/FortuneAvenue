uniform sampler2D texture;
uniform float time;
uniform float intensity;  // Intensidad del efecto

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec2 offset = vec2(sin(uv.y * 10.0 + time) * intensity, cos(uv.x * 10.0 + time) * intensity);
    gl_FragColor = texture2D(texture, uv + offset);
}
