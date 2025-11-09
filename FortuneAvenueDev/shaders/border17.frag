// Fragment shader - border effect
uniform sampler2D texture;
uniform vec2 texSize;
uniform float time;
uniform float thickness;
uniform vec4 outlineColor;

vec4 tex(vec2 uv){ return texture2D(texture, uv); }


void main(){
    vec2 uv = gl_TexCoord[0].xy - vec2(0.5);
    float a = tex(uv+vec2(0.5)).a;
    float r = length(uv);
    float maxA=0.0;
    for (float i=0;i<360;i+=12.0){
        float ang = radians(i) + time*1.0;
        vec2 off = vec2(cos(ang), sin(ang)) * (thickness/texSize.x*10.0);
        maxA = max(maxA, tex(uv+vec2(0.5)+off).a);
    }
    if (a>0.0) gl_FragColor = tex(uv+vec2(0.5));
    else if (maxA>0.0) gl_FragColor = vec4(outlineColor.rgb, 1.0);
    else discard;
}
