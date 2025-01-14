uniform float time;
uniform sampler2D texture;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    
    // Desplazamiento para simular las ondas
    uv.y += sin(uv.x * 10.0 + time) * 0.05;
    uv.x += cos(uv.y * 10.0 + time) * 0.05;
    
    vec4 color = texture2D(texture, uv);
    gl_FragColor = color;
}
