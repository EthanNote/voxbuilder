#version 400

uniform sampler2D color_texture;
uniform sampler2D normal_texture;
uniform sampler2D index_texture;

uniform vec3 light_direction;
uniform int option;

in vec2 uv;

layout(location = 0) out vec4 color;

void main(){

    if(option == 0){

    if(length(light_direction)>0)
        color = texture(color_texture, uv) + vec4(texture(normal_texture, uv).rgb*light_direction, 0);
    else    
        color = texture(color_texture, uv);
    }
    else if(option == 1){
        color = texture(index_texture, uv);
    }
}