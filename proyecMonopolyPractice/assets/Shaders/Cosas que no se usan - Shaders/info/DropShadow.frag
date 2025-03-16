uniform sampler2D texture;
uniform vec2 offset;
uniform vec4 shadowColor;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 shadow = texture2D(texture, uv + offset) * shadowColor;
    vec4 color = texture2D(texture, uv);
    
    gl_FragColor = max(color, shadow);
}
