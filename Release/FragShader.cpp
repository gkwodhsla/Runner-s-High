#include "FragShader.hpp"

GLint FragShader::createAndCompile()
{
	std::ifstream is(fileDir);
	std::vector<std::string> readSource;
	std::string buffer;
	while (is.peek() != EOF)
	{
		std::getline(is, buffer);
		readSource.emplace_back(buffer);
	}
	buffer.clear();
	readSource[0] = readSource[0] + '\n';
	for (auto&e : readSource)
	{
		buffer += e;
	}
	source = const_cast<GLchar*>(buffer.c_str());

	shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, bufferSize, NULL, errorLog);
		std::cerr << "ERROR: Fragment shader compile fail...\n" << errorLog << std::endl;
		return false;
	}
}
GLuint FragShader::retShader()
{
	return shader;
}