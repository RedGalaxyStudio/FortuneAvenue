uniform float time;
uniform sampler2D texture;

void main() {
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    float alpha = sin(time) * 0.5 + 0.5;  // Oscila el alpha entre 0 y 1
    gl_FragColor = vec4(color.rgb, color.a * alpha);  // Aplica el alpha modificado
}
