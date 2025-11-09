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
    float maxA = 0.0;
    for (float x=-thickness;x<=thickness;x+=1.0) for (float y=-thickness;y<=thickness;y+=1.0) maxA = max(maxA, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) { gl_FragColor = tex(uv); return; }
    if (maxA>0.0) {
        float len = length(uv - vec2(0.5));
        float dash = step(0.5, fract(len*50.0 - time*10.0));
        if (dash > 0.5) gl_FragColor = outlineColor; else discard;
    }
}
