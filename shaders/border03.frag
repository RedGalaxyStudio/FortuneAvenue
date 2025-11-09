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
    float pulse = 0.5 + 0.5 * sin(time*3.0);
    float t = thickness * (1.0 + pulse*0.8);
    float maxA = 0.0;
    for (float x=-t; x<=t; x+=1.0) for (float y=-t; y<=t; y+=1.0) maxA = max(maxA, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (maxA>0.0) gl_FragColor = outlineColor * (0.6 + 0.4*pulse);
    else discard;
}
