uniform float time;
uniform sampler2D texture;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 color = texture2D(texture, uv);
    
    // Efecto de barrido de luz
    float sweep = smoothstep(0.0, 1.0, sin(time + uv.x * 5.0)) * 0.5;
    vec4 light = vec4(1.0, 1.0, 1.0, 1.0) * sweep;
    
    // Combina el barrido de luz con el color original
    gl_FragColor = color + light;
}
