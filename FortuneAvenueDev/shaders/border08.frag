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
    float l = tex(uv + vec2(-1.0, -1.0)/texSize).a - tex(uv + vec2(1.0,1.0)/texSize).a;
    vec4 base = tex(uv);
    vec3 light = vec3(0.6 + l*0.8);
    gl_FragColor = vec4(base.rgb * light, base.a);
}
