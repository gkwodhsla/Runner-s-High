#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm/glm.hpp"
#include "GL/glm/ext.hpp"
#include "GL/glm/gtc/matrix_transform.hpp"

enum class ITEM_DIRECTION
{
	LEFT,
	RIGHT,
	MIDDLE
};

//폴리곤이 생성되는 위치 길이 3방향 있다 왼쪽, 오른쪽, 가운데 
class ItemAbstractClass
{
public:
	virtual void draw(GLint modelTransformLocation) = 0;
	virtual bool update(float) = 0;
	virtual float retItemZpos() = 0;
	virtual float retItemXpos() = 0;

	//update 함수에서 z값을 계속 감소시키다가 특정 z값에 도달하면 return true(객체가 사라짐.)
	//추가적으로 rads도 증가시킴!!
};

class Item :public ItemAbstractClass
{
public:
	Item(ITEM_DIRECTION initDirection);
	virtual void draw(GLint modelTransformLocation) override;
	virtual bool update(float)override;
	virtual float retItemZpos() { return ItemZpos; };
	virtual float retItemXpos() { return ItemXpos; };
	~Item();
private:
	float ItemXpos;
	float ItemYpos;
	float ItemZpos;
	float rads;//rads각도만큼 폴리곤이 y축기준으로 회전한다.
	unsigned int VAO, VBO, VBOC;
	glm::mat4 transMatrix;
	GLvoid initMatrix();
};

