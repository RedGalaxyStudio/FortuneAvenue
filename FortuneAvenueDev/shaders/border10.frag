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
    float t = thickness*1.0;
    float maxA = 0.0;
    for (float x=-t;x<=t;x+=1.0) for (float y=-t;y<=t;y+=1.0) maxA = max(maxA, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (maxA>0.0) {
        float lines = 40.0;
        float stripe = step(0.5, fract((uv.y + time*0.05)*lines));
        gl_FragColor = mix(vec4(0.0), outlineColor, stripe*0.9);
    } else discard;
}
