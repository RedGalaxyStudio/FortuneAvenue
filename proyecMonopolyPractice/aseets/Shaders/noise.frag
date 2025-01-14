uniform sampler2D texture;
uniform float time;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 color = texture2D(texture, uv);
    
    // Agregar ruido
    float noise = rand(uv + time);
    color.rgb += noise * 0.05;  // Intensidad del ruido
    
    gl_FragColor = color;
}
