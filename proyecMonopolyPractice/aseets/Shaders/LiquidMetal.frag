uniform sampler2D texture;
uniform float time;
uniform float speed;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec2 offset = vec2(sin(time * speed) * 0.1, cos(time * speed) * 0.1);
    gl_FragColor = texture2D(texture, uv + offset);
}
