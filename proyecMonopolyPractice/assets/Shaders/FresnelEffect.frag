uniform sampler2D texture;
uniform vec3 viewDir;  // Dirección de la cámara
uniform float fresnelPower;  // Controla el efecto de fresnel

void main() {
    vec3 normal = normalize(gl_FragCoord.xyz);
    float fresnel = pow(1.0 - dot(normal, viewDir), fresnelPower);
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = vec4(texColor.rgb + fresnel, texColor.a);
}
