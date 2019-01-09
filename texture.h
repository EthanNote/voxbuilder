#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<memory>
#include<string>
#include<map>
#include<vector>
enum TextureUnit {
#ifdef GL_TEXTURE0
	TEXTURE0 = GL_TEXTURE0,
#endif
#ifdef GL_TEXTURE1
	TEXTURE1 = GL_TEXTURE1,
#endif
#ifdef GL_TEXTURE2
	TEXTURE2 = GL_TEXTURE2,
#endif
#ifdef GL_TEXTURE3
	TEXTURE3 = GL_TEXTURE3,
#endif
#ifdef GL_TEXTURE4
	TEXTURE4 = GL_TEXTURE4,
#endif
#ifdef GL_TEXTURE5
	TEXTURE5 = GL_TEXTURE5,
#endif
#ifdef GL_TEXTURE6
	TEXTURE6 = GL_TEXTURE6,
#endif
#ifdef GL_TEXTURE7
	TEXTURE7 = GL_TEXTURE7,
#endif
#ifdef GL_TEXTURE8
	TEXTURE8 = GL_TEXTURE8,
#endif
#ifdef GL_TEXTURE9
	TEXTURE9 = GL_TEXTURE9,
#endif
#ifdef GL_TEXTURE10
	TEXTURE10 = GL_TEXTURE10,
#endif
#ifdef GL_TEXTURE11
	TEXTURE11 = GL_TEXTURE11,
#endif
#ifdef GL_TEXTURE12
	TEXTURE12 = GL_TEXTURE12,
#endif
#ifdef GL_TEXTURE13
	TEXTURE13 = GL_TEXTURE13,
#endif
#ifdef GL_TEXTURE14
	TEXTURE14 = GL_TEXTURE14,
#endif
#ifdef GL_TEXTURE15
	TEXTURE15 = GL_TEXTURE15,
#endif
};


class CTexture;
typedef std::shared_ptr<CTexture> Texture;

class CTexture
{
	GLuint name=-1;	
	GLuint binding = 0;

public:
	GLuint GetName();
	void Bind(GLuint unit);
	GLuint Bind();
	GLuint GetBinding();
	CTexture();
	~CTexture();
	static Texture Create(int width, int height);
	static Texture CreateDepth(int width, int height);
	static Texture Create(std::string fname);
};

//class CTextureBinding
//{
//	std::map<Texture, TextureUnit> unit;
//public:
//	CTextureBinding();
//	~CTextureBinding();
//
//	TextureUnit operator [](Texture texture);
//
//};

