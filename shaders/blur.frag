const int MAX_KERNEL_SIZE = 128;
uniform sampler2D tex;
uniform int arraySize;
uniform vec2 offsets[MAX_KERNEL_SIZE]; 
uniform float kernel[MAX_KERNEL_SIZE];
void main(void) { 
    // Fill this in!
    
    vec2 pos = gl_TexCoord[0].st;
    
    vec4 sum = vec4(0.0);
    for (int i = 0; i < arraySize; i++) {
        vec2 opos = pos + offsets[i].st;
        sum += kernel[i] * texture2D(tex, opos);
    }
    gl_FragColor = sum;
}
