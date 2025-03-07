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
    vec4 color = vec4(a, a, a, 1.0) * vec4(frag_LightColor, 1.0);  

    // Usar la textura en lugar del color del segmento
    vec4 textureColor = texture2D(segmentTexture, gl_TexCoord[0].xy);
    
    // Aplicar el brillo a la textura
    gl_FragColor = vec4(textureColor.rgb * color.rgb * 1.5, textureColor.a); // Ajustar el brillo
}
