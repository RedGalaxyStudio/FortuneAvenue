uniform float time;
uniform sampler2D texture;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    
    // Genera un pequeño desplazamiento basado en el tiempo para el efecto glitch
    float offset = fract(sin(uv.y * 10.0 + time * 5.0) * 43758.5453);
    
    if (mod(uv.y * 10.0 + time * 10.0, 20.0) < 1.0) {  // Glitch solo en ciertas líneas
        uv.x += offset * 0.1;
    }
    
    vec4 color = texture2D(texture, uv);
    gl_FragColor = color;
}

