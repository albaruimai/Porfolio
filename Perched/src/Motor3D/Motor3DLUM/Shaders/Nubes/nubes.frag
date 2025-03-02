#version 330 core
out vec4 FragColor;

in float LightIntensity;
in vec3 Position;
in vec2 TexCoord;
uniform int TIME_FROM_INIT;

uniform float gradient[256];
uniform sampler2D texture_diffuse1;
vec2 Offset = vec2(0.0,0.0);

float fade(float t)
{
    return t*t*t*(t*(t*6.0-15.0)+10.0);
}



float rand(vec2 co){
    return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
   
}

vec2 grad(vec2 p){
    float a = rand(p) * 2.0 * 3.1415926;
    return vec2(cos(a), sin(a)); 
}

float noise(vec2 p){
    vec2 p0 = floor(p);
    vec2 p1 = p0 + vec2(1.0,0.0);
    vec2 p2 = p0 + vec2(0.0,1.0);
    vec2 p3 = p0 + vec2(1.0,1.0);

    vec2 g0 = grad(p0);
    vec2 g1 = grad(p1);
    vec2 g2 = grad(p2);
    vec2 g3 = grad(p3);

    float t0 = p.x - p0.x;
    float fade_t0 = fade(t0);
    float t1 = p.y - p0.y;
    float fade_t1 = fade(t1);

    float p0p1 = (1.0-fade_t0)*dot(g0,(p-p0)) + fade_t0*dot(g1,(p-p1));
    float p2p3 = (1.0-fade_t0)*dot(g2,(p-p2)) + fade_t0*dot(g3,(p-p3));

    return ((1.0-fade_t1)*p0p1 + fade_t1*p2p3);
}



void main()
{
    float offset = float(TIME_FROM_INIT)*0.5;
    Offset = vec2(-offset,offset);
  
    float fog_maxdist = 250.0;
    float fog_mindist = 0.1;

    // Calculate fog
    float dist = gl_FragCoord.y;
    float fog_factor = (fog_maxdist - dist) /
                  (fog_maxdist - fog_mindist);
    fog_factor = clamp(fog_factor, 0.0, 0.7);

    //vec4 Ambient = vec4(texture(texture_diffuse1, TexCoord)) * 0.0f;


    float n = noise(vec2(gl_FragCoord.x+Offset.x,gl_FragCoord.y+Offset.y)/256.0)*1.0 +
              noise(vec2(gl_FragCoord.x+Offset.x,gl_FragCoord.y+Offset.y)/128.0) * 0.5 +
              noise(vec2(gl_FragCoord.x+Offset.x,gl_FragCoord.y+Offset.y)/64.0) * 0.25 +
              noise(vec2(gl_FragCoord.x+Offset.x,gl_FragCoord.y+Offset.y)/32.0) * 0.125;


    FragColor = vec4(vec3(n*0.8+0.5),fog_factor);

}
