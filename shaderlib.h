/*
Auto generated by shader_lib_gen.py
*/
#include "shader.h"



class CVoxShader : public CShader{
public:
    UniformMatrix MVP;
    UniformMatrix MV;
    void Load();
    void LocateUniforms();
};

typedef std::shared_ptr<CVoxShader> VoxShader;

class CAxisShader : public CShader{
public:
    UniformMatrix MVP;
    void Load();
    void LocateUniforms();
};

typedef std::shared_ptr<CAxisShader> AxisShader;

class CSkyboxShader : public CShader{
public:
    UniformMatrix VP_inv;
    void Load();
    void LocateUniforms();
};

typedef std::shared_ptr<CSkyboxShader> SkyboxShader;

namespace shaderlib{
    // generated shader objects
    extern VoxShader vox_shader;
    extern AxisShader axis_shader;
    extern SkyboxShader skybox_shader;

    void loadshaders();
}
