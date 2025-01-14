uniform sampler2D texture;

void main() {
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    // Aplicar un filtro de tono sepia
    float r = dot(color.rgb, vec3(0.393, 0.769, 0.189));
    float g = dot(color.rgb, vec3(0.349, 0.686, 0.168));
    float b = dot(color.rgb, vec3(0.272, 0.534, 0.131));

    gl_FragColor = vec4(r, g, b, color.a);
}
