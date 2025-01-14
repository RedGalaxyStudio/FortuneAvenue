uniform sampler2D texture;

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    vec4 color = texture2D(texture, texCoord);
    
    float kernel[9] = float[9]( -1, -1, -1,
                                -1,  8, -1,
                                -1, -1, -1 );
    
    vec3 result = vec3(0.0);
    for (int i = 0; i < 9; i++) {
        vec2 offset = vec2((i % 3) - 1, (i / 3) - 1) * 1.0;
        result += texture2D(texture, texCoord + offset * 0.001).rgb * kernel[i];
    }
    gl_FragColor = vec4(result, 1.0);
}
