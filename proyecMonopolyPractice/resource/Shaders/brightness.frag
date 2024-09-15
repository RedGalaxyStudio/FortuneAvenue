uniform sampler2D texture;
uniform float brightness;

void main() {
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    
    // Aumentar el brillo multiplicando por un valor
    gl_FragColor = vec4(color.rgb * brightness, color.a);
}
