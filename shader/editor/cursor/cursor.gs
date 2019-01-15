#version 400

layout(points) in;
layout(line_strip, max_vertices = 24) out;

in ivec3 cursor_pos[];

uniform mat4 MVP;

void main(){
    float x = cursor_pos[0].x;
    float y = cursor_pos[0].y;
    float z = cursor_pos[0].z;
    gl_Position = MVP*vec4(x+0.5, 0, z+0.5, 1);
    EmitVertex();
    gl_Position = MVP*vec4(x+0.5, 32, z+0.5, 1);
    EmitVertex();
    EndPrimitive();

    gl_Position = MVP*vec4(0, y+0.5, z+0.5, 1);
    EmitVertex();
    gl_Position = MVP*vec4(32, y+0.5, z+0.5, 1);
    EmitVertex();
    EndPrimitive();

    gl_Position = MVP*vec4(x+0.5, y+0.5, 0, 1);
    EmitVertex();
    gl_Position = MVP*vec4(x+0.5, y+0.5, 32, 1);
    EmitVertex();
    EndPrimitive();
}