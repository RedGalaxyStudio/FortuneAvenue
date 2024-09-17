uniform sampler2D texture;
uniform float distortionAmount;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec2 distortedUV = uv + vec2(sin(uv.y * 10.0) * distortionAmount, cos(uv.x * 10.0) * distortionAmount);
    gl_FragColor = texture2D(texture, distortedUV);
}
