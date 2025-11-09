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
    float maxA=0.0;
    for (float x=-thickness-1.0;x<=thickness+1.0;x+=1.0) for (float y=-thickness-1.0;y<=thickness+1.0;y+=1.0) maxA=max(maxA, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (maxA>0.0) {
        float edge = maxA * (1.0 - smoothstep(0.0, 1.0, length(uv-vec2(0.5))));
        gl_FragColor = vec4(vec3(0.8,0.85,1.0)*edge, 1.0);
    } else discard;
}
