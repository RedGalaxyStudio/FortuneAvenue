uniform sampler2D texture;
uniform float shiftAmount;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec2 offset = vec2(sin(shiftAmount), cos(shiftAmount)) * 0.01;
    vec4 texColor = texture2D(texture, uv + offset);
    gl_FragColor = texColor;
}
