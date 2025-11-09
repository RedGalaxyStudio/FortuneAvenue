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
    float inner=0.0, outer=0.0;
    for (float x=-thickness; x<=thickness; x+=1.0) for (float y=-thickness; y<=thickness; y+=1.0) inner = max(inner, tex(uv+vec2(x,y)/texSize).a);
    for (float x=-(thickness*3.0); x<=thickness*3.0; x+=1.0) for (float y=-(thickness*3.0); y<=thickness*3.0; y+=1.0) outer = max(outer, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (inner>0.0) gl_FragColor = outlineColor;
    else if (outer>0.0) gl_FragColor = outlineColor * 0.5;
    else discard;
}
