uniform sampler2D texture;
uniform float scanlineIntensity;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    float scanline = step(0.5, mod(gl_FragCoord.y, 2.0)) * scanlineIntensity;
    vec4 texColor = texture2D(texture, uv);
    gl_FragColor = vec4(texColor.rgb - scanline, texColor.a);
}
