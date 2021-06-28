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
//폴리곤이 생성되는 위치 길이 3방향 있다 왼쪽, 오른쪽, 가운데 
class PolygonAbstractClass
{
public:
	virtual void draw(GLint modelTransformLocation)=0;
	virtual bool update(float)=0;
	virtual float retPolygonZpos() { return NULL; };
	virtual float retPolygonXpos() { return NULL; };
	virtual bool ChangePolygonRotateType() { return NULL; };

	//update 함수에서 z값을 계속 감소시키다가 특정 z값에 도달하면 return true(객체가 사라짐.)
	//추가적으로 rads도 증가시킴!!
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
	float rads;//rads각도만큼 폴리곤이 y축기준으로 회전한다.
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