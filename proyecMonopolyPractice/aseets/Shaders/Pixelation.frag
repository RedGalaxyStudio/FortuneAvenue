uniform sampler2D texture;
uniform float pixelSize;  // Tamaño del "pixel"

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec2 pixelCoord = floor(uv / pixelSize) * pixelSize;
    gl_FragColor = texture2D(texture, pixelCoord);
}
