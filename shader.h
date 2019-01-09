#pragma once

#include "uniform.h"



class CShader;
class CBlockShader;
class CScreenShader;

typedef std::shared_ptr<CShader> Shader;
typedef std::shared_ptr<CBlockShader> BlockShader;
typedef std::shared_ptr<CScreenShader> ScreenShader;

class CShader
{
protected:
	unsigned int program;
	//void LocateUniform(std::string name, Uniform* uniform);
public:
	void LocateUniform(std::string name, Uniform & uniform);
	void Load(const char * vs, const char * fs, const char * gs);
	void UseProgram();
	CShader();
	~CShader();

	static Shader Create(); 
};




//class CBlockShader : public CShader {
//public:
//	UniformMatrix mvp;
//	UniformMatrix mv;
//	CBlockShader();
//
//	static BlockShader Create();
//};
//
//
//class CScreenShader : public CShader {
//public:
//
//	//UniformInt tex;
//	UniformSampler2DArray textures;
//	UniformMatrix projection;
//	UniformVec3Array ssao_kernel;
//	static ScreenShader Create();
//};
