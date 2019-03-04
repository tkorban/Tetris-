#version 150

in vec4 myPosition;
in vec4 myColor;
out vec4 color;

uniform int xCoordinate;
uniform int yCoordinate;

void 
main() 
{
    mat4 value = mat4(2.0/xCoordinate, 0.0, 0.0, 0.0, 0.0, 2.0/yCoordinate, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    vec4 newPosition = myPosition + vec4(-200, -360, 0, 0);
    gl_Position = newPosition * value;
    color = myColor;
}