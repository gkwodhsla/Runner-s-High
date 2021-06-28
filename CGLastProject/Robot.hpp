#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm/glm.hpp"
#include "GL/glm/ext.hpp"
#include "GL/glm/gtc/matrix_transform.hpp"
#include <vector>
class Robot
{
public:
	Robot();
	void draw(GLint modelTransformLocation, GLint objColorLocation);
	void update(float);
	void changeXpos(float deltaX) { xVelocity += deltaX; }
	void changeYpos(float deltaY) { robotYpos += deltaY; }
	float retRobotXpos() { return robotXpos; }
	float retRobotZpos() { return robotZpos; }
	~Robot();
private:
	float robotXpos;
	float robotYpos;
	float robotZpos;
	unsigned int VAO[6];
	unsigned int VBO[6];
	unsigned int VBON[6];
	float bodyRads;
	float xVelocity;
	bool isBodyUp;
	//팔이랑 다리가 들리고있는가
	static std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	static std::vector<glm::vec3> temp_vertices;
	static std::vector<glm::vec2> temp_uvs;
	static std::vector<glm::vec3> temp_normals;
	static std::vector<glm::vec3> outvertex, outnormal;
	static std::vector<glm::vec2> outuv;
	static std::vector<glm::vec3> verticiesForVBO;
	static std::vector<glm::vec3> normalsForVBON;
	static float sumX,sumY, sumZ;
	static float aveX, aveY, aveZ;
	static float scaleX, scaleY, scaleZ;
	static float minX, minY, minZ;
	static float maxX, maxY, maxZ;
	static float scaleAll;

	glm::mat4 transMatrix;
	GLvoid initMatrix();
	int loadObj(const char* filename);
};