#version 400

layout(location=0) out vec4 color;
uniform mat4 VP_inv;

in vec2 pos;

void main(){
    // color = vec4(pos,0.0,1.0);
    vec4 worldpos = VP_inv*vec4(pos, 1.0, 1.0);
    vec3 ground = vec3(0.05,0.1,0.05);
    vec3 sky = vec3(0.3,0.5,0.7);
    vec3 fog = vec3(0.8,0.8,0.8);
    if(worldpos.y>0){
        float factor = 1-pow(2, -worldpos.y*5);
        if(factor>1){
            factor=1;
        }
        color = vec4(sky*factor+fog*(1-factor), 1.0);
    }
    else{
        float factor = 1-pow(2, worldpos.y*100);
        if(factor>1){
            factor=1;
        }
        color = vec4(ground*factor+fog*(1-factor), 1.0);
    }
    // color = vec4(worldpos.y,worldpos.y,worldpos.y,1.0);
}