#include "texture.h"




CTexture::CTexture()
{
	glGenTextures(1, &this->name);
}


CTexture::~CTexture()
{
	glDeleteTextures(1, &this->name);
	this->name = -1;
}

GLuint CTexture::GetName()
{
	return name;
}

#define BINDING_SIZE 32

CTexture* binded_textures[BINDING_SIZE] = { 0 };
int loop_binding_index = 0;

void CTexture::Bind(GLuint unit)
{
	if (unit<GL_TEXTURE0 || unit>GL_TEXTURE31) {
		for (int i = 0; i < BINDING_SIZE; i++) {
			if (!binded_textures[i]) {
				unit = GL_TEXTURE0 + i;
				Bind(unit);
				return;
			}
		}
	}
	if (unit<GL_TEXTURE0 || unit>GL_TEXTURE31) {
		if (loop_binding_index > 31) {
			loop_binding_index = 0;
		}
		unit = GL_TEXTURE0 + loop_binding_index;
		loop_binding_index++;
		Bind(unit);
		return;
	}


	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D, this->name);
	this->binding = unit;
	binded_textures[unit - GL_TEXTURE0] = this;

}

GLuint CTexture::Bind()
{
	Bind(0);
	return this->binding;
}

GLuint CTexture::GetBinding()
{
	return this->binding;
}

void CTexture::ReadPixel(double x, double y, glm::vec4 & out)
{
}

inline void set_t2d_params() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}


Texture CTexture::Create(int width, int height)
{
	auto T = Texture(new CTexture);

	glBindTexture(GL_TEXTURE_2D, T->name);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	
	set_t2d_params();

	return T;
	
}

Texture CTexture::CreateDepth(int width, int height)
{
	auto T = Texture(new CTexture);

	glBindTexture(GL_TEXTURE_2D, T->name);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	set_t2d_params();

	return T;
}



//
//CTextureBinding::CTextureBinding()
//{
//}
//
//
//CTextureBinding::~CTextureBinding()
//{
//}
//
//TextureUnit CTextureBinding::operator[](Texture  texture)
//{
//	auto v = this->unit[texture];
//	if (v) {
//		return v;
//	}
//
//	else {
//		auto u = TextureUnit(this->unit.size()-1 + TextureUnit::TEXTURE0);
//		this->unit[texture] = u;
//		if (unit.size() > 8) {
//			unit.
//		}
//		return u;
//	}
//}
