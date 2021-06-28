#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm/glm.hpp"
#include "GL/glm/ext.hpp"
#include "GL/glm/gtc/matrix_transform.hpp"

class Ground
{
public:
	Ground();
	void draw(GLint modelTransformLocation, GLint objColorLocation);
	void update(float);
	void changeXpos(float deltaX) { xVelocity += deltaX; }
	void changeZpos(float deltaZ) { groundZpos += deltaZ; }
	void changeYpos(float deltaY) { groundYpos += deltaY; }
	float retGroundXpos() { return groundXpos; }
	float retGroundZpos() { return groundZpos; }
	float retGroundYpos() { return groundYpos; }
	int plane_type = 0;
	~Ground();
private:
	float xVelocity;
	float groundXpos;
	float groundYpos;
	float groundZpos;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int VBON;
	unsigned int texture[3];


	glm::mat4 transMatrix;
	GLvoid initMatrix();

};