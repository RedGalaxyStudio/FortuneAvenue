uniform sampler2D texture;
uniform float time;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 texColor = texture2D(texture, uv);
    float noise = (sin(time) + cos(time)) * 0.1;  // Ruido de película
    vec4 noiseColor = vec4(noise, noise, noise, 1.0);
    gl_FragColor = texColor + noiseColor;
}
