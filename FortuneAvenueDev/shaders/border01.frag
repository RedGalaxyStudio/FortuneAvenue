// Fragment shader - border effect
uniform sampler2D texture;
uniform vec2 texSize;
uniform float time;
uniform float thickness;
uniform vec4 outlineColor;

vec4 tex(vec2 uv){ return texture2D(texture, uv); }


void main() {
    vec2 uv = gl_TexCoord[0].xy;
    float a = tex(uv).a;
    // Usa time para modificar el color azul del borde con un pulso sutil
    float pulse = 0.5 + 0.5 * sin(time * 6.2831); // valor entre 0 y 1

    if (a > 0.0) {
        gl_FragColor = tex(uv);
        return;
    }
    float maxA = 0.0;
    float t = max(1.0, thickness);
    for (float x=-t; x<=t; x+=1.0) {
        for (float y=-t; y<=t; y+=1.0) {
            vec2 off = vec2(x,y)/texSize;
            maxA = max(maxA, tex(uv+off).a);
        }
    }
    if (maxA > 0.0) {
        // Color con pulso dinámico
        vec4 pulseColor = outlineColor;
        pulseColor.b *= pulse; // modula el canal azul
        gl_FragColor = pulseColor;
    } else discard;
}
