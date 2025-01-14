// lightShader.frag
uniform vec2 frag_LightOrigin;	
uniform vec3 frag_LightColor; 	
uniform float frag_LightAttenuation;	
uniform vec2 frag_ScreenResolution; 
uniform sampler2D segmentTexture; // Uniforme para la textura del segmento

void main() {		
    vec2 baseDistance = gl_FragCoord.xy; 
    baseDistance.y = frag_ScreenResolution.y - baseDistance.y; 
    float d = length(frag_LightOrigin - baseDistance); 
    float a = 1.0 / (frag_LightAttenuation * d + 0.1); // Ajustar la atenuación
    
    // Muestrea el color de la textura
    vec4 textureColor = texture(segmentTexture, gl_TexCoord[0].xy); // Asume que la coordenada de textura está en gl_TexCoord[0]
    
    // Usar el color de la textura y multiplicarlo por el brillo
    gl_FragColor = vec4(textureColor.rgb * a, textureColor.a); // Ajustar brillo
}