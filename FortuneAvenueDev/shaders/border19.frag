// Fragment shader - border effect
uniform sampler2D texture;
uniform vec2 texSize;
uniform float time;
uniform float thickness;
uniform vec4 outlineColor;

vec4 tex(vec2 uv){ return texture2D(texture, uv); }


float rand(vec2 co){ return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453); }
void main(){
    vec2 uv = gl_TexCoord[0].xy;
    float a = tex(uv).a;
    float maxA=0.0;
    for (float x=-thickness;x<=thickness;x+=1.0) for (float y=-thickness;y<=thickness;y+=1.0) maxA=max(maxA, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (maxA>0.0){
        float noise = rand(vec2(floor(uv.x*100.0), floor(uv.y*100.0) + floor(time*5.0)));
        if (noise > 0.3) gl_FragColor = outlineColor;
        else discard;
    } else discard;
}
