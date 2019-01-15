#version 400

layout(location=0) in ivec3 postion;

out ivec3 cursor_pos;

void main(){
    cursor_pos = postion;
}