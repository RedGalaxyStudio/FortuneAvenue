uniform sampler2D texture;
uniform vec3 glowColor;
uniform float glowStrength;
uniform float time;  // Variable de tiempo para efectos dinámicos

void main() {
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);
    
    // Utiliza la variable de tiempo para crear un efecto de pulso
    float pulse = abs(sin(time * 3.0)) * 0.5 + 0.5;  // Pulsa entre 0 y 1

    // Calcula el brillo de neón con el pulso
    vec3 glow = glowColor * glowStrength * pulse;
    
    // Aplica el brillo al color del texto
    gl_FragColor = vec4(texColor.rgb + glow, texColor.a);
}