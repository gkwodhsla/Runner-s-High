#define _CRT_SECURE_NO_WARNINGS
#include "Robot.hpp"
#include<atlfile.h>

std::vector<unsigned int> Robot::vertexIndices, Robot::uvIndices, Robot::normalIndices;
std::vector<glm::vec3> Robot::temp_vertices;
std::vector<glm::vec2> Robot::temp_uvs;
std::vector<glm::vec3> Robot::temp_normals;
std::vector<glm::vec3> Robot::outvertex, Robot::outnormal;
std::vector<glm::vec2> Robot::outuv;
std::vector<glm::vec3> Robot::verticiesForVBO;
std::vector<glm::vec3> Robot::normalsForVBON;
float Robot::sumX=0.0, Robot::sumY=0.0, Robot::sumZ=0.0;
float Robot::aveX, Robot::aveY, Robot::aveZ;
float Robot::scaleX, Robot::scaleY, Robot::scaleZ;
float Robot::minX = -20.0, Robot::minY = -20.0, Robot::minZ = -20.0;
float Robot::maxX = 20.0, Robot::maxY = 20.0, Robot::maxZ = 20.0;
float Robot::scaleAll;

//float color[6][108];
std::vector<std::vector<float>> color;
void initColor()
{
	color.resize(7);
	for (int i = 0; i < 7; ++i)
		color[i].resize(108);
	for (int i = 0; i < 108; i += 3)
	{
		color[0][i] = 1.0f;
		color[0][i + 1] = 1.0f;
		color[0][i + 2] = 1.0f;
		//¸ö»ö
		color[1][i] = 1.0f;
		color[1][i + 1] = 0.0f;
		color[1][i + 2] = 0.0f;
		color[2][i] = 1.0f;
		color[2][i + 1] = 0.0f;
		color[2][i + 2] = 0.0f;
		//¾çÆÈ
		color[3][i] = 0.0f;
		color[3][i + 1] = 1.0f;
		color[3][i + 2] = 0.0f;
		color[4][i] = 0.0f;
		color[4][i + 1] = 1.0f;
		color[4][i + 2] = 0.0f;
		//¾ç´Ù¸®
		color[5][i] = 0.0f;
		color[5][i + 1] = 0.0f;
		color[5][i + 2] = 1.0f;
		//¸Ó¸®
		color[6][i] = 1.0f;
		color[6][i + 1] = 0.0f;
		color[6][i + 2] = 1.0f;
		//ÄÚ
	}
}
Robot::Robot()
{
	robotXpos = 0.0f;
	robotYpos = 0.0f;
	robotZpos = 5.0f;
	isBodyUp = true;
	bodyRads = 0.0f;
	xVelocity = 0.0f;
	transMatrix = glm::mat4(1.0f);
	loadObj("cube.obj");
	for (int i = 0; i < vertexIndices.size(); ++i)
		--vertexIndices[i];
	for (int i = 0; i < normalIndices.size(); ++i)
		--normalIndices[i];
	for (int i = 0; i < vertexIndices.size(); ++i)
	{
		verticiesForVBO.emplace_back(glm::vec3(temp_vertices[vertexIndices[i]].x, temp_vertices[vertexIndices[i]].y, temp_vertices[vertexIndices[i]].z));
	}
	for (int i = 0; i < normalIndices.size(); ++i)
	{
		normalsForVBON.emplace_back(glm::vec3(temp_normals[normalIndices[i]].x, temp_normals[normalIndices[i]].y, temp_normals[normalIndices[i]].z));
	}
	initColor();

	glGenVertexArrays(6, VAO);
	glGenBuffers(6, VBO);
	glGenBuffers(6, VBON);
	for (int i = 0; i < 6; ++i)
	{
		glBindVertexArray(VAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, verticiesForVBO.size()*sizeof(glm::vec3), &verticiesForVBO[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBON[i]);
		glBufferData(GL_ARRAY_BUFFER, normalsForVBON.size() * sizeof(glm::vec3), &normalsForVBON[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		glEnableVertexAttribArray(1);

	}
}

void Robot::draw(GLint modelTransformLocation, GLint objColorLocation)

{
	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos, robotYpos, robotZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(0.8f, 1.0f, 0.5f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//¸öÅë
	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos - 1.2f, robotYpos, robotZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(0.3f, 0.8f, 0.3f));
	transMatrix = glm::rotate(transMatrix, glm::radians(bodyRads), glm::vec3(1.0f, 0.0f, 0.0f));

	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glUniform3f(objColorLocation, 1.0f, 0.0f, 0.0f);
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//¿ÞÆÈ

	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos + 1.2f, robotYpos, robotZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(0.3f, 0.8f, 0.25f));
	transMatrix = glm::rotate(transMatrix, glm::radians(-bodyRads), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glUniform3f(objColorLocation, 1.0f, 0.0f, 0.0f);
	glBindVertexArray(VAO[2]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//¿À¸¥ÆÈ

	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos - 0.5f, robotYpos - 2.0f, robotZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(0.3f, 1.0f, 0.25f));
	transMatrix = glm::rotate(transMatrix, glm::radians(-bodyRads), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glUniform3f(objColorLocation, 0.0f, 1.0f, 0.0f);
	glBindVertexArray(VAO[3]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//¿Þ´Ù¸®

	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos + 0.5f, robotYpos - 2.0f, robotZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(0.3f, 1.0f, 0.5f));
	transMatrix = glm::rotate(transMatrix, glm::radians(bodyRads), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glUniform3f(objColorLocation, 0.0f, 1.0f, 0.0f);
	glBindVertexArray(VAO[4]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	////¿À¸¥´Ù¸®

	initMatrix();
	transMatrix = glm::scale(transMatrix, glm::vec3(0.6f, 0.6f, 0.4f));
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos + (robotXpos*0.7f), robotYpos + 2.5f, robotZpos + (robotZpos*1.5f)));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glUniform3f(objColorLocation, 0.0f, 0.0f, 1.0f);
	glBindVertexArray(VAO[5]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	////¸Ó¸®
}

void Robot::update(float velocity)
{
	if (isBodyUp)
	{
		bodyRads += velocity / 2.0f;
		if (bodyRads >= 45.0f)
			isBodyUp = false;
	}
	else
	{
		bodyRads -= velocity / 2.0f;
		if (bodyRads <= -45.0f)
			isBodyUp = true;
	}
	if (xVelocity > 0.0)
	{
		if (robotXpos <= 8.0f)
			robotXpos += xVelocity;
	}
	else
	{
		if (robotXpos >= -8.0f)
			robotXpos += xVelocity;
	}
}

void Robot::initMatrix()
{
	glLoadIdentity();
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			transMatrix[i][j] = 0.0f;
		}
	}
	transMatrix[0][0] = 1.0f;
	transMatrix[1][1] = 1.0f;
	transMatrix[2][2] = 1.0f;
	transMatrix[2][2] = 1.0f;
	transMatrix[3][3] = 1.0f;

}

Robot::~Robot()
{
	glDeleteBuffers(6, VBO);
	glDeleteVertexArrays(6, VAO);
}

int Robot::loadObj(const char* filename)

{
	FILE* objFile;

	fopen_s(&objFile, filename, "rb");

	if (objFile == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(objFile, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (vertex.x < minX) minX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z > maxZ) maxZ = vertex.z;
			sumX += vertex.x;
			sumY += vertex.y;
			sumZ += vertex.z;

			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	aveX = sumX / vertexIndices.size();
	aveY = sumY / vertexIndices.size();
	aveZ = sumZ / vertexIndices.size();
	scaleX = (1.0 - maxX) * 10 + 1;
	scaleY = (1.0 - maxY) * 10 + 1;
	scaleZ = (1.0 - maxZ) * 10 + 1;

	if (scaleX > scaleY) {
		if (scaleY > scaleZ)
			scaleAll = scaleZ;
		else
			scaleAll = scaleY;
	}
	else if (scaleX < scaleY) {
		if (scaleX < scaleZ)
			scaleAll = scaleX;
		else
			scaleAll = scaleZ;
	}


	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		outvertex.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 vertex = temp_uvs[uvIndex - 1];
		outuv.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[normalIndex - 1];
		outnormal.push_back(vertex);
	}

	return outvertex.size();
}