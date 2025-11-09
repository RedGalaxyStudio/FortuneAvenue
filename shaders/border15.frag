// Fragment shader - border effect
uniform sampler2D texture;
uniform vec2 texSize;
uniform float time;
uniform float thickness;
uniform vec4 outlineColor;

vec4 tex(vec2 uv){ return texture2D(texture, uv); }


float hash(vec2 p){ return fract(sin(dot(p,vec2(127.1,311.7)))*43758.5453123); }
float noise(vec2 p){
    vec2 i = floor(p);
    vec2 f = fract(p);
    float a = hash(i);
    float b = hash(i + vec2(1.0,0.0));
    float c = hash(i + vec2(0.0,1.0));
    float d = hash(i + vec2(1.0,1.0));
    vec2 u = f*f*(3.0-2.0*f);
    return mix(a,b,u.x) + (c-a)*u.y*(1.0-u.x) + (d-b)*u.x*u.y;
}
void main(){
    vec2 uv = gl_TexCoord[0].xy;
    float a = tex(uv).a;
    float maxA=0.0;
    for (float x=-thickness;x<=thickness;x+=1.0) for (float y=-thickness;y<=thickness;y+=1.0) maxA=max(maxA, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (maxA>0.0){
        float n = noise(uv*texSize*0.3 + time*0.5);
        gl_FragColor = vec4(outlineColor.rgb * (0.6 + 0.4*n), 1.0);
    } else discard;
}
