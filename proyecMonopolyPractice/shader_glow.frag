// glow.frag
uniform sampler2D texture;
uniform vec2 resolution;

void main() {
    vec2 texCoord = gl_FragCoord.xy / resolution;
    
    vec4 color = texture2D(texture, texCoord);
    
    // Calcular la distancia desde el centro
    float dist = length(texCoord - vec2(0.5, 0.5)); // Ajustar según el tamaño de tu círculo

    // Controlar el brillo
    float glow = smoothstep(0.4, 0.5, dist); // Ajusta estos valores para controlar el área del brillo

    // Solo aumentar el brillo en la parte exterior
    gl_FragColor = vec4(color.rgb + vec3(0.3) * glow, color.a); // Ajustar la intensidad del resplandor
}
