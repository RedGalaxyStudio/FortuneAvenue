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
    float inner=1.0;
    for (float x=-thickness;x<=thickness;x+=1.0) for (float y=-thickness;y<=thickness;y+=1.0) inner = min(inner, tex(uv+vec2(x,y)/texSize).a);
    float shadow = smoothstep(0.0, 1.0, inner);
    vec4 base = tex(uv);
    gl_FragColor = vec4(base.rgb * (0.4 + 0.6*shadow), base.a);
}
