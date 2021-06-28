#pragma once
#include "shader.hpp"
#include<string>
#include<vector>
class VertexShader :public Shader
{
public:
	VertexShader(std::string _fileDir):fileDir(_fileDir)
	{}
	virtual GLint createAndCompile() override;
	virtual GLuint retShader() override;

	virtual ~VertexShader()
	{glDeleteShader(shader);}
private:
	std::string fileDir;
	GLchar* source;
	GLuint shader;
	GLint result;
	const int bufferSize = 512;
	GLchar errorLog[512];
};