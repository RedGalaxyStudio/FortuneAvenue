uniform sampler2D texture;
uniform float time;
uniform vec3 pulseColor;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 texColor = texture2D(texture, uv);
    float pulse = abs(sin(time)) * 0.5 + 0.5;
    gl_FragColor = vec4(texColor.rgb * (1.0 + pulseColor * pulse), texColor.a);
}
