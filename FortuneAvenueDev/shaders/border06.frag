// Fragment shader - border effect
uniform sampler2D texture;
uniform vec2 texSize;
uniform float time;
uniform float thickness;
uniform vec4 outlineColor;

vec4 tex(vec2 uv){ return texture2D(texture, uv); }


void main(){
    vec2 uv = gl_TexCoord[0].xy;
    vec2 offset = vec2(0.02, -0.02);
    float a = tex(uv).a;
    float sh = 0.0;
    for (float x=-4.0;x<=4.0;x+=1.0) for (float y=-4.0;y<=4.0;y+=1.0) sh += tex(uv + offset + vec2(x,y)/texSize).a;
    sh = sh / (9.0*9.0);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (sh>0.01) gl_FragColor = vec4(0.0,0.0,0.0, sh*0.8);
    else discard;
}
