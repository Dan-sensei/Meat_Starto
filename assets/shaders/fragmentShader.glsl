uniform vec2 frag_LightOrigin;
uniform float frag_LightAttenuation;
uniform vec2 screenSize;

void main()
{
    vec3 blue = vec3(204, 255, 255);
    vec2 baseDistance =  gl_FragCoord.xy;

    baseDistance.y = screenSize.y-baseDistance.y;

    vec2 distance=frag_LightOrigin - baseDistance;

    float linear_distance = length(distance);
    float attenuation=4.0/( frag_LightAttenuation*linear_distance + frag_LightAttenuation*linear_distance);

    vec4 lightColor = vec4(blue, 1.0);

    vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * lightColor;

    gl_FragColor=color;
}
