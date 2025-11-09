// Fragment shader - border effect
uniform sampler2D texture;
uniform vec2 texSize;
uniform float time;
uniform float thickness;
uniform vec4 outlineColor;

vec4 tex(vec2 uv){ return texture2D(texture, uv); }


void main(){
    vec2 uv = gl_TexCoord[0].xy;
    float a = tex(uv).a;
    if (a<0.01) discard;
    float minA = 1.0;
    for (float x=-thickness;x<=thickness;x+=1.0) for (float y=-thickness;y<=thickness;y+=1.0) minA = min(minA, tex(uv+vec2(x,y)/texSize).a);
    float glow = 1.0 - minA;
    vec4 c = tex(uv);
    gl_FragColor = mix(c, outlineColor, glow*0.8);
}
