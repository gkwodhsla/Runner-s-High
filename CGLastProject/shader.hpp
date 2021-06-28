#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm/glm.hpp"
#include "GL/glm/ext.hpp"
#include "GL/glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <fstream>
class Shader
{
public:
	Shader() = default;
	virtual GLint createAndCompile() = 0;
	virtual GLuint retShader() = 0;
	virtual ~Shader() = default;
};