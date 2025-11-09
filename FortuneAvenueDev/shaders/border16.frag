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
    float accum = 0.0;
    float R = thickness*6.0;
    for (float x=-R;x<=R;x+=1.0) for (float y=-R;y<=R;y+=1.0) accum += tex(uv+vec2(x,y)/texSize).a;
    accum /= ((2.0*R+1.0)*(2.0*R+1.0));
    if (a>0.0) gl_FragColor = tex(uv);
    else if (accum>0.01) gl_FragColor = vec4(outlineColor.rgb, accum*0.6);
    else discard;
}
