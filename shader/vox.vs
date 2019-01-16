#version 400
layout(location = 0) in ivec4 vox;
layout(location = 1) in ivec2 props;

out ivec3 vox_pos;
out int vox_size;
out int vox_palette_index;
out int vox_face_mask;

void main(){
    vox_pos = vox.xyz;
    vox_size = vox.w;
    vox_palette_index = props.x;
    vox_face_mask = props.y;
}