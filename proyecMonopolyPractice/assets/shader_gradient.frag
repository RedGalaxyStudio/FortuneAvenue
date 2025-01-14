uniform vec2 resolution;
uniform vec3 segmentColor; // Color del segmento actual
uniform vec2 center;       // Centro del círculo

void main() {
    vec2 texCoord = gl_FragCoord.xy / resolution;

    // Calcula la distancia del píxel al centro del círculo
    vec2 fromCenter = gl_FragCoord.xy - center;
    float distance = length(fromCenter) / (resolution.x * 0.5); // Normaliza la distancia

    // Usa el color del segmento como base
    vec3 color = segmentColor;

    // Mezcla el color con blanco de manera radial
    color = mix(color, vec3(1.0, 1.0, 1.0), distance * 0.5); // Degradado más sutil con blanco

    gl_FragColor = vec4(color, 1.0); // Color final
}

