uniform sampler2D texture;
uniform float aberrationAmount;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 r = texture2D(texture, uv + vec2(aberrationAmount, 0.0));
    vec4 g = texture2D(texture, uv);
    vec4 b = texture2D(texture, uv - vec2(aberrationAmount, 0.0));
    gl_FragColor = vec4(r.r, g.g, b.b, g.a);
}
