#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main()
{
    vec2 coord = gl_PointCoord - vec2(0.5); // center at (0,0)
    
    float dist = length(coord);

    if(dist > 0.5)
        discard; // cut corners → circle

    FragColor = vec4(ourColor, 1.0);
}