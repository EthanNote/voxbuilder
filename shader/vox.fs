// flat in vec4 color;
in vec4 view_pos;
flat in vec3 world_normal;
flat in int color_palette_index;

layout(location=0) out vec4 color_out;
layout(location=1) out vec4 normal_out;
layout(location=2) out vec4 position_out;

uniform vec4 palette[625];

void main () {
    //gl_FragColor=color;
    color_out = palette[color_palette_index];
    position_out = view_pos;
    normal_out = vec4(world_normal, 1.0);
};