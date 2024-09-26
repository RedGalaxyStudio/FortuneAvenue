uniform sampler2D texture;
uniform vec2 resolution;   // Tamaño de la pantalla
uniform vec2 mousePos;     // Posición del cursor (en coordenadas normalizadas: 0.0 a 1.0)
uniform float time;        // Tiempo para animar las ondas

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec2 mouse = mousePos * resolution;   // Convertimos las coordenadas normalizadas a coordenadas de la pantalla
    
    // Calculamos la distancia entre cada píxel y la posición del cursor
    float dist = distance(uv * resolution, mouse);
    
    // Generamos una onda usando una función seno que varía con la distancia al cursor y el tiempo
    float wave = sin(dist * 0.1 - time * 5.0) * 0.01;
    
    // Desplazamos la textura en la dirección de la onda
    vec2 displacedUV = uv + normalize(uv - mousePos) * wave;
    
    // Obtenemos el color desplazado de la textura
    vec4 color = texture2D(texture, displacedUV);
    
    // Aplicamos el color final
    gl_FragColor = color;
}
