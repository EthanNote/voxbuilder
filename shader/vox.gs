#version 400
layout(points) in;
layout(triangle_strip, max_vertices = 24) out;


in ivec3 vox_pos[];
in int vox_size[];
in int vox_palette_index[];
in int vox_face_mask[];

// flat out vec4 color;
out vec4 view_pos;
flat out vec3 world_normal;
flat out int color_palette_index;

uniform mat4 MVP;
uniform mat4 MV;

vec4 v[8];

void face_vertex(int a, int b, int c, int d){
    gl_Position  = MVP * v[a];
        view_pos = MV  * v[a];
    EmitVertex();
    gl_Position  = MVP * v[b];
        view_pos = MV  * v[b];
    EmitVertex();
    gl_Position  = MVP * v[c];
        view_pos = MV  * v[c];
    EmitVertex();
    gl_Position  = MVP * v[d];
        view_pos = MV  * v[d];
    EmitVertex();
    EndPrimitive();
}

void main(){
    vec4 pos = vec4(vox_pos[0],1.0);

    if(vox_palette_index[0]<0 || vox_size[0]<=0){
        EndPrimitive();
        return;
    }

    v[0] = pos;
    v[1] = pos + vec4(vox_size[0], 0.0,         0.0,         0.0);
    v[2] = pos + vec4(0.0,         vox_size[0], 0.0,         0.0);
    v[3] = pos + vec4(vox_size[0], vox_size[0], 0.0,         0.0);
    v[4] = pos + vec4(0.0,         0.0,         vox_size[0], 0.0);
    v[5] = pos + vec4(vox_size[0], 0.0,         vox_size[0], 0.0);
    v[6] = pos + vec4(0.0,         vox_size[0], vox_size[0], 0.0);
    v[7] = pos + vec4(vox_size[0], vox_size[0], vox_size[0], 0.0);

    // z-
    // color = vec4(0.5,0.5,0.0,1.0);
    world_normal = vec3(0.0, 0.0, -1.0);
    face_vertex(0,1,2,3);

    // z+
    // color = vec4(0.0, 0.0, 1.0, 1.0);
    world_normal = vec3(0.0, 0.0, 1.0);
    face_vertex(4,5,6,7);

    // x-
    // color = vec4(0.0, 0.5, 0.5, 1.0);
    world_normal = vec3(-1.0, 0.0, 0.0);
    face_vertex(0,4,2,6);

    // x+
    // color = vec4(1.0, 0.0, 0.0, 1.0);
    world_normal = vec3(1.0, 0.0, 0.0);
    face_vertex(1,5,3,7);

    // y-
    // color = vec4(0.5, 0.0, 0.5, 1.0);
    world_normal = vec3(0.0, -1.0, 0.0);
    face_vertex(0,1,4,5);

    // y+
    // color = vec4(0.0, 1.0, 0.0, 1.0);
    world_normal = vec3(0.0, 1.0, 0.0);
    face_vertex(2,3,6,7);
}