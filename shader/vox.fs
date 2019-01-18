#version 400
in vec4 view_pos;
flat in vec3 world_normal;
flat in int color_palette_index;
flat in int vox_id;
flat in int vox_face_id;

uniform int selection_id;
uniform float time;
uniform vec3 highlight_color;

layout(location=0) out vec4 color_out;
layout(location=1) out vec4 normal_out;
layout(location=2) out vec4 position_out;
layout(location=3) out vec4 index_out;

// uniform vec4 palette[625];

void main () {
    //gl_FragColor=color;
    //color_out = palette[color_palette_index];
    //color_out = vec4(1.0,0.0,0.0,1.0);
    vec3 color = world_normal;
    if(vox_id == selection_id){
        float weight = sin(time)*0.25 + 0.5;
        color = color*(1-weight) + highlight_color*weight;
    }

    color_out = vec4(color ,1.0);


    position_out = view_pos;
    normal_out = vec4(world_normal, 1.0);
    index_out = vec4((vox_id%32)/32.0, vox_face_id/6.0, 0, 0);
};