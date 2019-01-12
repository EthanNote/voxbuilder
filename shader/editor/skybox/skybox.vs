#version 400

layout(location = 0) in vec2 vpos;

out vec2 pos;
void main(){
    gl_Position = vec4(vpos, 0.0,1.0);
    pos = vpos;
}