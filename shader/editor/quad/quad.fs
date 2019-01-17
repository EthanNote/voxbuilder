#version 400

uniform sampler2D color_texture;
uniform sampler2D normal_texture;
uniform vec3 light_direction;

in vec2 uv;

layout(location = 0) out vec4 color;

void main(){
    if(length(light_direction)>0)
        color = texture(color_texture, uv) + vec4(texture(normal_texture, uv).rgb*light_direction, 0);
    else    
        color = texture(color_texture, uv);
}