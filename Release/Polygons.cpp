#define _CRT_SECURE_NO_WARNINGS
#include "Polygons.hpp"
#include<atlfile.h>
#include<vector>
using namespace std;


float cubeCoords[] =
{
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,//아랫면
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,1.0f,-1.0f,
	-1.0f,1.0f,1.0f,//왼쪽옆면
	1.0f,1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f,//오른쪽옆면
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,1.0f,1.0f,
	-1.0f,1.0f,1.0f,//정면
	-1.0f,1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,1.0f,-1.0f,//뒷면
	-1.0f,1.0f,-1.0f,
	-1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,1.0f,-1.0f//윗면

};


float pyramidCoords[] =
{
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,//여기까지 밑면
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	0.0f,1.0f,0.0f,//여기까지 앞면
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	0.0f,1.0f,0.0f,//여기까지 뒷면
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,1.0f,
	0.0f,1.0f,0.0f,//여기까지 오른면
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,
	0.0f,1.0f,0.0f,//여기까지 왼면

};

float cubeColor[] =
{
	 0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f

};
float pyramidColor[] =
{
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
};


std::vector<unsigned int> Cube::vertexIndices, Cube::uvIndices, Cube::normalIndices;
std::vector<glm::vec3> Cube::temp_vertices;
std::vector<glm::vec2> Cube::temp_uvs;
std::vector<glm::vec3> Cube::temp_normals;
std::vector<glm::vec3> Cube::outvertex, Cube::outnormal;
std::vector<glm::vec2> Cube::outuv;
std::vector<glm::vec3> Cube::verticiesForVBO;
std::vector<glm::vec3> Cube::normalsForVBON;
float Cube::sumX = 0.0, Cube::sumY = 0.0, Cube::sumZ = 0.0;
float Cube::aveX, Cube::aveY, Cube::aveZ;
float Cube::scaleX, Cube::scaleY, Cube::scaleZ;
float Cube::minX = -20.0, Cube::minY = -20.0, Cube::minZ = -20.0;
float Cube::maxX = 20.0, Cube::maxY = 20.0, Cube::maxZ = 20.0;
float Cube::scaleAll;
bool Cube::isInitial = false;

Pyramid::Pyramid(POLYGON_DIRECTION initDirection)
{
	if (initDirection == POLYGON_DIRECTION::LEFT)
		pyramidXpos = -7.0f;
	else if (initDirection == POLYGON_DIRECTION::MIDDLE)
		pyramidXpos = 0.0f;
	else pyramidXpos = 7.0f;
	pyramidYpos = 0.0f;
	pyramidZpos = -15.0f;
	rads = 0.0f;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glGenBuffers(1, &VBON);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidCoords), &pyramidCoords[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

}
void Pyramid::draw(GLint modelTransformLocation)
{
	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(pyramidXpos-0.0f, pyramidYpos, pyramidZpos));
	transMatrix = glm::rotate(transMatrix, glm::radians(rads), glm::vec3(0.0f, 1.0f, 0.0f));
	transMatrix = glm::scale(transMatrix, glm::vec3(1.5f, 2.0f, 1.5f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0,24);
}
bool Pyramid::update(float velocity)
{
	
	if (isCurshRotate)
	{
		pyramidYpos += 1.0f;
		pyramidXpos += 1.0f;
		pyramidZpos -= 2.0f;
		rads += velocity * 4;
	}
	else
	{
		rads += velocity / 2.0f;
		pyramidZpos += 0.05f*velocity;

	}
	if (!isCurshRotate && pyramidZpos >= 6.0f)
		return true;
	else if (isCurshRotate && pyramidZpos <= -36.0f)
		return true;
	return false;

}
Pyramid::~Pyramid()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Pyramid::initMatrix()
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

Cube::Cube(POLYGON_DIRECTION initDirection)
{
	if (initDirection == POLYGON_DIRECTION::LEFT)
		cubeXpos = -7.0f;
	else if (initDirection == POLYGON_DIRECTION::MIDDLE)
		cubeXpos = 0.0f;
	else cubeXpos = 7.0f;
	cubeYpos = 0.0f;
	cubeZpos = -15.0f;
	rads = 0.0f;
	if (!isInitial)
	{
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
		isInitial = true;
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glGenBuffers(1, &VBON);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticiesForVBO.size() * sizeof(glm::vec3), &verticiesForVBO[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBON);
	glBufferData(GL_ARRAY_BUFFER, normalsForVBON.size() * sizeof(glm::vec3), &normalsForVBON[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(1);


}
void Cube::draw(GLint modelTransformLocation)
{
	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(cubeXpos, cubeYpos, cubeZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(1.5f, 2.0f, 1.5f));
	transMatrix = glm::rotate(transMatrix, glm::radians(rads), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
bool Cube::update(float velocity)
{
	if (isCurshRotate)
	{
		cubeYpos += 1.0f;
		cubeXpos -= 1.0f;
		cubeZpos -= 2.0f;
		rads += velocity * 4;
	
	}
	else
	{
		rads += velocity / 2.0f;
		cubeZpos += 0.05f*velocity;
	}
	if (!isCurshRotate && cubeZpos >= 6.0f)
		return true;
	else if (isCurshRotate && cubeZpos <= -36.0f)
		return true;
	return false;
}
Cube::~Cube()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}
void Cube::initMatrix()
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

int Cube::loadObj(const char* filename)

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