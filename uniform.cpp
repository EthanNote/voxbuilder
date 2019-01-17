#include <GL/glew.h>
#include "uniform.h"


//void UniformMatrix::Set(void * value)
//{
//	glUseProgram(this->program);
//	glUniformMatrix4fv(this->location, 1, this->transpose, (GLfloat*)value);
//	glUseProgram(0);
//}

void UniformMatrix::Set(glm::mat4 & mat)
{
	glUseProgram(this->program);
	glUniformMatrix4fv(this->location, 1, this->transpose, (GLfloat*)&mat[0][0]);
	glUseProgram(0);
	//this->Set(&mat[0][0]);
}

//void UniformVec4::Set(void * value)
//{
//	glUseProgram(this->program);
//	glUniform4fv(this->location, 1, (GLfloat*)value);
//	glUseProgram(0);
//}

void UniformVec4::Set(glm::vec4 & vec)
{
	glUseProgram(this->program);
	glUniform4fv(this->location, 1, &vec[0]);
	glUseProgram(0);
}

//void UniformInt::Set(void * value)
//{
//	glUseProgram(this->program);
//	glUniform1i(this->location, (GLint)value);
//	glUseProgram(0);
//}

void UniformInt::Set(int value)
{
	glUseProgram(this->program);
	glUniform1i(this->location, (GLint)value);
	glUseProgram(0);
}

//void UniformIntArray::Set(void * value)
//{
//	throw "Unable set array via `Set(void * value)`, use `Set(std::vector<int>& integers)` instead.";
//}

void UniformIntArray::Set(std::vector<int>& integers)
{
	glUseProgram(this->program);
	glUniform1iv(this->location, integers.size(), &integers[0]);
	glUseProgram(0);
}

void UniformSampler2D::Set(TextureUnit unit)
{
	return UniformInt::Set((int)(unit - TextureUnit::TEXTURE0));
}

void UniformSampler2D::Set(Texture texture)
{
	auto binding = texture->GetBinding();
	if (!binding) {
		texture->Bind();
	}
	return UniformInt::Set(texture->GetBinding() - GL_TEXTURE0);
}

void UniformSampler2DArray::Set(std::vector<TextureUnit>& units)
{
	auto v = std::vector<int>(units.size(), 0);
	auto vi = v.begin();
	auto ui = units.begin();
	while (vi != v.end())
	{
		*vi = *ui - TextureUnit::TEXTURE0;
		vi++;
		ui++;
	}
	UniformIntArray::Set(v);
	/*glUseProgram(this->program);
	glUniform1iv(this->location, integers.size(), &integers[0]);
	glUseProgram(0);*/
}

void UniformVec3Array::Set(int vectorCount, float * buffer)
{
	glUseProgram(this->program);
	//glUniform1iv(this->location, integers.size(), &integers[0]);
	glUniform3fv(this->location, vectorCount, buffer);
	glUseProgram(0);
}

void UniformVec4Array::Set(int vectorCount, float * buffer)
{
	glUseProgram(this->program);
	//glUniform1iv(this->location, integers.size(), &integers[0]);
	glUniform4fv(this->location, vectorCount, buffer);
	glUseProgram(0);
}

void UniformVec3::Set(glm::vec3 & vec)
{
	glUseProgram(this->program);
	glUniform3fv(this->location, 1, &vec[0]);
	glUseProgram(0);
}
