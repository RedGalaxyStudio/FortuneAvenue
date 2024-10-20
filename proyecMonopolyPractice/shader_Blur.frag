// blur.frag
uniform vec2 resolution;

void main() {
    vec2 texCoord = gl_FragCoord.xy / resolution; // Obtener coordenadas normalizadas
    vec3 color = vec3(0.0);
    float blurAmount = 1.0 / resolution.x; // Ajusta el valor para más o menos desenfoque

    for (float x = -1.0; x <= 1.0; x += 1.0) {
        for (float y = -1.0; y <= 1.0; y += 1.0) {
            vec2 offset = vec2(x * blurAmount, y * blurAmount);
            color += vec3(0.5) * 0.5; // Color medio o puedes poner el color que desees
        }
    }

    color /= 9.0; // Promedia los colores
    gl_FragColor = vec4(color, 1.0); // Color final
}
