#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<vector>
#include<memory>

#include<glm/glm.hpp>
#include "texture.h"

class Uniform {
public:
	unsigned int program = -1;
	int location = -1;
	//virtual void Set(void* value) = 0;
};

class UniformMatrix : public Uniform {
	//virtual void Set(void* value) override;
public:
	bool transpose = false;
	void Set(glm::mat4 & mat);
};

class UniformVec3 : public Uniform {
	//virtual void Set(void* value) override;
public:
	void Set(glm::vec3 & vec);
};

class UniformVec4 : public Uniform {
	//virtual void Set(void* value) override;
public:
	void Set(glm::vec4 & vec);
};


class UniformInt : public Uniform {
	//virtual void Set(void* value) override;
public:
	void Set(int value);
};

class UniformFloat : public Uniform {
	//virtual void Set(void* value) override;
public:
	void Set(float value);
};

class UniformSampler2D : public UniformInt {
public:
	void Set(TextureUnit unit);
	void Set(Texture texture);
};

class UniformIntArray : public Uniform {
	//virtual void Set(void* value) override;
public:
	void Set(std::vector<int> & integers);
};

class UniformVec3Array : public Uniform {
public:
	void Set(int vectorCount, float* buffer);
};

class UniformVec4Array : public Uniform {
public:
	void Set(int vectorCount, float* buffer);
};

class UniformSampler2DArray : public UniformIntArray {
public:
	void Set(std::vector<TextureUnit> & units);
};