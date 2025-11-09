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
    vec4 c = tex(uv);
    vec4 glow = vec4(0.0);
    float r = thickness + 4.0;
    for (float x=-r; x<=r; x+=1.0) {
        for (float y=-r; y<=r; y+=1.0) {
            vec2 off = vec2(x,y)/texSize;
            glow += tex(uv+off) * 0.08;
        }
    }
    glow *= outlineColor;
    if (a > 0.0) gl_FragColor = c + glow * 0.6;
    else if (glow.a > 0.0) gl_FragColor = outlineColor * 0.9;
    else discard;
}
