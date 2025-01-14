uniform sampler2D texture;

void main() {
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    
    // Invertir los componentes de color
    gl_FragColor = vec4(1.0 - color.rgb, color.a);
}
