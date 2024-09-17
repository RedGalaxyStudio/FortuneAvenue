uniform sampler2D texture;
uniform vec3 glowColor;
uniform float glowIntensity;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 texColor = texture2D(texture, uv);
    vec3 glow = glowColor * glowIntensity;
    gl_FragColor = vec4(texColor.rgb + glow, texColor.a);
}
