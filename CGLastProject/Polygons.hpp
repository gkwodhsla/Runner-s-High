#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm/glm.hpp"
#include "GL/glm/ext.hpp"
#include "GL/glm/gtc/matrix_transform.hpp"
#include <vector>
enum class POLYGON_DIRECTION
{
	LEFT,
	RIGHT,
	MIDDLE
};
//�������� �����Ǵ� ��ġ ���� 3���� �ִ� ����, ������, ��� 
class PolygonAbstractClass
{
public:
	virtual void draw(GLint modelTransformLocation)=0;
	virtual bool update(float)=0;
	virtual float retPolygonZpos() { return NULL; };
	virtual float retPolygonXpos() { return NULL; };
	virtual bool ChangePolygonRotateType() { return NULL; };

	//update �Լ����� z���� ��� ���ҽ�Ű�ٰ� Ư�� z���� �����ϸ� return true(��ü�� �����.)
	//�߰������� rads�� ������Ŵ!!
};

class Pyramid:public PolygonAbstractClass
{
public:
	Pyramid(POLYGON_DIRECTION initDirection);
	virtual void draw(GLint modelTransformLocation) override;
	virtual bool update(float)override;
	float retPolygonZpos() { return pyramidZpos;};
	float retPolygonXpos() { return pyramidXpos; };
	bool ChangePolygonRotateType() { isCurshRotate = true; return isCurshRotate; };
	~Pyramid();
private:
	float pyramidXpos;
	float pyramidYpos;
	float pyramidZpos;
	bool isCurshRotate = false;
	float rads;//rads������ŭ �������� y��������� ȸ���Ѵ�.
	unsigned int VAO, VBO, VBON;
	glm::mat4 transMatrix;
	
	GLvoid initMatrix();

};

class Cube:public PolygonAbstractClass
{
public:
	Cube(POLYGON_DIRECTION initDirection);
	virtual void draw(GLint modelTransformLocation) override;
	virtual bool update(float)override;
	float retPolygonZpos() { return cubeZpos; };
	float retPolygonXpos() { return cubeXpos; };
	bool ChangePolygonRotateType() { isCurshRotate = true; return isCurshRotate; };
	int rotate_type = 0;
	~Cube();
private:
	float cubeXpos;
	float cubeYpos;
	float cubeZpos;
	float rads;
	unsigned int VAO, VBO, VBON;
	glm::mat4 transMatrix;
	bool isCurshRotate = false;
	static std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	static std::vector<glm::vec3> temp_vertices;
	static std::vector<glm::vec2> temp_uvs;
	static std::vector<glm::vec3> temp_normals;
	static std::vector<glm::vec3> outvertex, outnormal;
	static std::vector<glm::vec2> outuv;
	static std::vector<glm::vec3> verticiesForVBO;
	static std::vector<glm::vec3> normalsForVBON;
	static float sumX, sumY, sumZ;
	static float aveX, aveY, aveZ;
	static float scaleX, scaleY, scaleZ;
	static float minX, minY, minZ;
	static float maxX, maxY, maxZ;
	static float scaleAll;
	static bool isInitial;
	GLvoid initMatrix();
	int loadObj(const char* filename);
};