
varying vec3 vertex;		// The position of the vertex, in eye space
varying vec3 light;		// The normalized vector from the vertex to the light
varying vec3 eye;		// The normalized vector from the vertex to the eye
varying vec3 normal;		// The normal vector of the vertex, in eye space

uniform samplerCube envMap;	// The cube map containing the environment to reflect
uniform vec4 ambient;		// The ambient channel of the color to reflect
uniform vec4 diffuse;		// The diffuse channel of the color to reflect
uniform vec4 specular;		// The specular channel of the color to reflect
    
uniform float r0;		// The Fresnel reflectivity when the incident angle is 0
uniform float m;		// The roughness of the material

void main()
{
    vec3 n = normalize(normal);
    vec3 l = normalize(light);
    vec3 e = normalize(eye);
    
    float kd = max(0, dot(n, l));
    
    vec3 r = reflect(-l, n);
    
    vec3 i = normalize(vertex - eye);
    vec3 h = normalize(l - i);
    
    vec3 look = gl_ModelViewMatrixInverse * vec4(reflect(-e, n), 0);
    
    float alpha = acos(dot(n, h));
    float d = exp(-tan(alpha) * tan(alpha) / (m * m)) / (3.14 * m * m * pow(cos(alpha), 4.));
    float g = min(min(1., (2. * dot(h, n) * dot(e, n)) / dot(e, h)),
			  (2. * dot(h, n) * dot(l, n)) / dot(e, h));
    float f = r0 + (1. - r0) * pow(1. - dot(-i, n), 5.);
    
    float ks = max(0, d * f * g / dot(e, n));
    
    gl_FragColor = mix(ambient + kd * diffuse + ks * specular, textureCube(envMap, look), f);
}
