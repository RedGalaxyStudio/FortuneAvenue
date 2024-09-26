uniform sampler2D texture;
uniform float mosaicSize;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec2 mosaicUV = floor(uv / mosaicSize) * mosaicSize;
    gl_FragColor = texture2D(texture, mosaicUV);
}
