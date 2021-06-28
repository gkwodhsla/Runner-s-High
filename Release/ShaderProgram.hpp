#pragma once

#include"FragShader.hpp"
#include"VertexShader.hpp"
#include<initializer_list>
class ShaderProgram
{
public:
	ShaderProgram() = default;
	GLuint attachAndLink(std::initializer_list<GLuint> list)
	{
		ShaderProgramID = glCreateProgram();
		for (auto&e : list)
		{
			glAttachShader(ShaderProgramID, e);
		}
		glLinkProgram(ShaderProgramID);
		glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(ShaderProgramID, bufferSize, NULL, errorLog);
			std::cerr << "ERROR:shader program linking fali\n" << errorLog << std::endl;
			return false;
		}
	}
	GLuint retProgramID()
	{return ShaderProgramID;}
	virtual ~ShaderProgram() = default;
private:
	GLuint ShaderProgramID;
	GLint result;
	int bufferSize = 512;
	GLchar errorLog[512];
};