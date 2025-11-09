// Fragment shader - border effect
uniform sampler2D texture;
uniform vec2 texSize;
uniform float time;
uniform float thickness;
uniform vec4 outlineColor;

vec4 tex(vec2 uv){ return texture2D(texture, uv); }


vec4 sampleShift(vec2 uv, float dx, float dy){
    vec4 r = texture2D(texture, uv + vec2(dx,dy)/texSize);
    return r;
}
void main(){
    vec2 uv = gl_TexCoord[0].xy;
    float a = tex(uv).a;
    float maxA=0.0;
    for (float x=-thickness;x<=thickness;x+=1.0) for (float y=-thickness;y<=thickness;y+=1.0) maxA=max(maxA, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (maxA>0.0){
        vec4 rc = sampleShift(uv, -2.0, 0.0);
        vec4 gc = sampleShift(uv, 0.0, 0.0);
        vec4 bc = sampleShift(uv, 2.0, 0.0);
        gl_FragColor = vec4(rc.r, gc.g, bc.b, 1.0);
    } else discard;
}
