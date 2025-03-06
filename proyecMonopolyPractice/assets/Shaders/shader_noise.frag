#version 330 core  // Asegúrate de que la versión sea la correcta

uniform vec2 resolution;
uniform sampler2D segmentTexture;  // Textura del segmento
uniform float noiseAmount;          // Cantidad de ruido a añadir

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vec2 texCoord = gl_FragCoord.xy / resolution;
    
    // Muestrea el color de la textura
    vec3 textureColor = texture(segmentTexture, texCoord).rgb;

    // Genera ruido y lo ajusta a un rango pequeño
    float noise = random(texCoord) * noiseAmount;  // Cambia noiseAmount para ajustar la cantidad de ruido

    // Añade el ruido al color de la textura
    vec3 color = textureColor + vec3(noise);

    // Asegura que los valores de color estén en el rango [0, 1]
    color = clamp(color, 0.0, 1.0);

    gl_FragColor = vec4(color, 1.0);  // Color final
}

