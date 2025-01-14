#version 120

uniform sampler2D texture;
uniform vec2 resolution;

void main()
{
    vec2 texCoord = gl_TexCoord[0].st;
    vec4 color = vec4(0.0);
    int blurSize = 10;  // Tamaño del desenfoque

    for (int x = -blurSize; x <= blurSize; x++)
    {
        for (int y = -blurSize; y <= blurSize; y++)
        {
            vec2 offset = vec2(x, y) / resolution;
            color += texture2D(texture, texCoord + offset) / float((blurSize * 2 + 1) * (blurSize * 2 + 1));
        }
    }

    gl_FragColor = color;
}
