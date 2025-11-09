// Fragment shader - border effect
uniform sampler2D texture;
uniform vec2 texSize;
uniform float time;
uniform float thickness;
uniform vec4 outlineColor;

vec4 tex(vec2 uv){ return texture2D(texture, uv); }


vec3 hsv2rgb(vec3 c){ vec3 p = abs(fract(c.xxx + vec3(0.0,2.0/3.0,1.0/3.0)) *6.0 -3.0); return c.z * mix(vec3(1.0), clamp(p-1.0,0.0,1.0), c.y); }
void main(){
    vec2 uv = gl_TexCoord[0].xy;
    float a = tex(uv).a;
    float t = time*0.4;
    float maxA=0.0;
    for (float x=-thickness*3.0;x<=thickness*3.0;x+=1.0) for (float y=-thickness*3.0;y<=thickness*3.0;y+=1.0) maxA = max(maxA, tex(uv+vec2(x,y)/texSize).a);
    if (a>0.0) gl_FragColor = tex(uv);
    else if (maxA>0.0){
        float hue = fract(uv.x + t*0.2);
        vec3 rgb = hsv2rgb(vec3(hue,1.0,1.0));
        float pulse = 0.5 + 0.5*sin(time*6.0);
        gl_FragColor = vec4(rgb * (0.6 + 0.6*pulse), 1.0);
    } else discard;
}
