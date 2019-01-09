layout(location = 0) in vec4 vox;
layout(location = ) in ivec2 props;

out vec3 vox_pos;
out float vox_size;
out int vox_palette_index;
out int vox_face_mask;

void main(){
    vox_pos = vox.xyz;
    vox_size = vox.w;
    vox_palette_index = props.x;
    vox_face_mask = props.y;
}