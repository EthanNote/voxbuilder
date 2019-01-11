#version 400
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

uniform mat4 MVP;
flat out vec3 vcolor;
void main(){
    gl_Position = MVP * vec4(pos, 1.0); 
    vcolor = color;
}