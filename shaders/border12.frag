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
    float t = thickness*2.0;
    for (float x=-t;x<=t;x+=1.0) for (float y=-t;y<=t;y+=1.0) maxA = max(maxA, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (maxA>0.0) {
        float dist = 1.0 - maxA;
        float alpha = smoothstep(0.0,1.0, 1.0 - dist);
        gl_FragColor = vec4(outlineColor.rgb, alpha*0.9);
    } else discard;
}
