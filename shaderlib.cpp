/*
Auto generated by shader_lib_gen.py
*/
#include <GL/glew.h>
#include "shaderlib.h"



void CVoxShader::LocateUniforms(){
    this->LocateUniform("MVP", this->MVP);
    this->LocateUniform("MV", this->MV);
}

void CVoxShader::Load(){
    CShader::Load("./shader/vox.vs", "./shader/vox.fs", "./shader/vox.gs");
}

void CAxisShader::LocateUniforms(){
    this->LocateUniform("MVP", this->MVP);
}

void CAxisShader::Load(){
    CShader::Load("./shader/editor/axis.vs", "./shader/editor/axis.fs", NULL);
}

void CSkyboxShader::LocateUniforms(){
    this->LocateUniform("VP_inv", this->VP_inv);
}

void CSkyboxShader::Load(){
    CShader::Load("./shader/editor/skybox/skybox.vs", "./shader/editor/skybox/skybox.fs", NULL);
}

// global shader objects
namespace shaderlib {
    VoxShader vox_shader = nullptr;
    AxisShader axis_shader = nullptr;
    SkyboxShader skybox_shader = nullptr;
}

void shaderlib::loadshaders(){

    vox_shader = VoxShader(new CVoxShader);
    vox_shader -> Load();
    vox_shader -> LocateUniforms();


    axis_shader = AxisShader(new CAxisShader);
    axis_shader -> Load();
    axis_shader -> LocateUniforms();


    skybox_shader = SkyboxShader(new CSkyboxShader);
    skybox_shader -> Load();
    skybox_shader -> LocateUniforms();

}
