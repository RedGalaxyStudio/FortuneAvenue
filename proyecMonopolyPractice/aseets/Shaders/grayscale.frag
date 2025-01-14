uniform sampler2D texture;

void main() {
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    
    // Promediar los componentes de color para obtener el gris
    float grayscale = (color.r + color.g + color.b) / 3.0;

    gl_FragColor = vec4(vec3(grayscale), color.a);
}
