uniform sampler2D texture;
uniform float time;
uniform float glitchAmount;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec2 glitchOffset = vec2(sin(time * 5.0) * glitchAmount, cos(time * 5.0) * glitchAmount);
    gl_FragColor = texture2D(texture, uv + glitchOffset);
}
